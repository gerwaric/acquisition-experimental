#include <acquisition/acquisition.h>

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/item.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/constants.h>
#include <acquisition/data_stores/league_data_store.h>
#include <acquisition/data_stores/user_data_store.h>
#include <acquisition/oauth/oauth_manager.h>
#include <acquisition/oauth/oauth_settings.h>
#include <acquisition/rate_limit/rate_limiter.h>
#include <acquisition/settings.h>
#include <acquisition/utils/command_line.h>
#include <acquisition/utils/utils.h>

#include <QsLog/QsLog.h>

#include <QDesktopServices>
#include <QDir>

#define SERVER_ENDPOINT "https://api.pathofexile.com"

Acquisition::Acquisition(QObject* parent) : QObject(parent)
{
    const QString banner_text("- Starting " APP_NAME " version " APP_VERSION_STRING " -");
    const QString banner_line(banner_text.length(), '-');

    QLOG_INFO() << banner_line;
    QLOG_INFO() << banner_text;
    QLOG_INFO() << banner_line;

    OAuthSettings oauth;
    oauth.authorization_url = "https://www.pathofexile.com/oauth/authorize";
    oauth.token_url = "https://www.pathofexile.com/oauth/token";
    oauth.client_id = "acquisition";
    oauth.client_scope = "account:leagues account:stashes account:characters";
    oauth.redirect_url = "http://127.0.0.1";
    oauth.redirect_path = "/auth/path-of-exile";

    m_network_manager = new QNetworkAccessManager(this);
    m_oauth_manager = new OAuthManager(*m_network_manager, oauth, this);
    m_rate_limiter = new RateLimiter(*m_network_manager, this);
    m_tree_model = new TreeModel(this);
    m_proxy_model = new ProxyModel(this);
    m_search_filters = new SearchFilters(this);

    m_proxy_model->setSourceModel(m_tree_model);

    connect(m_oauth_manager, &OAuthManager::accessGranted, this, &Acquisition::onAccessGranted);
}

void Acquisition::setDataDirectory(const QString& directory)
{
    QLOG_DEBUG() << "Acquisition: loading settings and data from" << directory;
    m_settings = new Settings(directory, this);
    m_user_data = new UserDataStore(directory, this);
    m_league_data = new LeagueDataStore(directory, this);

    loadSettings();
    initLeagueActions();
    initLoggingActions();
}

QString Acquisition::makeLogFilename(const QString& directory)
{
    return directory + QDir::separator() + "log-new.txt";
}

void Acquisition::loadSettings()
{
    QLOG_DEBUG() << "Acquisition: loading application settings";

    if (m_settings->username().isEmpty()) {
        QLOG_DEBUG() << "Acquisition: username is unset";
    } else {
        const QString username = m_settings->username();
        QLOG_DEBUG() << "Acquisition: username is" << username;
        m_user_data->setUsername(username);
        m_league_data->setUsername(username);
    };

    if (m_settings->league().isEmpty()) {
        QLOG_DEBUG() << "Acquisition: league is unset";
    } else {
        const QString league = m_settings->league();
        QLOG_DEBUG() << "Acquisition: league is" << league;
        m_league_data->setLeague(league);
    };

    m_characters = m_league_data->getCharacters();
    QLOG_DEBUG() << "Acquisition: loading" << m_characters->size() << "stored characters";
    for (size_t i = 0; i < m_characters->size(); ++i) {
        const poe_api::Character& character = *(*m_characters)[i];
        QLOG_TRACE() << "Acquisition: loading character" << i << "/" << m_characters->size() << character.name;
        m_tree_model->appendCharacter(character);
    }

    m_stashes = m_league_data->getStashes();
    QLOG_DEBUG() << "Application: loading" << m_stashes->size() << "stored stashes";
    for (size_t i = 0; i < m_stashes->size(); ++i) {
        const poe_api::StashTab& stash = *(*m_stashes)[i];
        QLOG_TRACE() << "Application: loading stash" << i << "/" << m_stashes->size() << stash.type + ":" << stash.name;
        m_tree_model->appendStash(stash);
    };

    emit searchResultsChanged();

    OAuthToken token = m_user_data->getStruct<OAuthToken>("oauth_token");
    if (token.isValid()) {
        QLOG_DEBUG() << "Acquisition: found an OAuth token valid until" << token.expiration.value_or(QDateTime());
        m_oauth_manager->setToken(token);
    };

}

void Acquisition::initLeagueActions()
{
    QLOG_DEBUG() << "Acquisition: initializing the league menu actions";
    const QString current_league = m_settings->league();
    if (!current_league.isEmpty()) {
        QLOG_DEBUG() << "Acquisition: creating league action for" << current_league;
        const QString display_name = utils::leaguePrettyName(current_league);
        QAction* action = new QAction(display_name, this);
        action->setCheckable(true);
        action->setChecked(true);
        action->setData(current_league);
        connect(action, &QAction::triggered, this, &Acquisition::setLeague);
        m_league_actions = { action };
    };
    emit leagueListChanged();
}

void Acquisition::initLoggingActions()
{
    QLOG_DEBUG() << "Acquisition: initializing the logging menu actions";
    const QsLogging::Level current_logging_level = m_settings->loggingLevel();

    m_logging_actions.clear();
    m_logging_actions.reserve(utils::logging_level_names.size());
    for (const auto& pair : utils::logging_level_names) {
        const QsLogging::Level level = pair.first;
        const char* name = pair.second;
        QLOG_DEBUG() << "Acquisition: creating logging action for" << level << name;
        QAction* action = new QAction(name, this);
        action->setCheckable(true);
        action->setChecked(level == current_logging_level);
        action->setData(level);
        connect(action, &QAction::triggered, this, &Acquisition::setLoggingLevel);
        m_logging_actions.append(action);
    };
}

void Acquisition::authenticate()
{
    QLOG_INFO() << "Acquisition: authentication has been started";
    m_oauth_manager->requestAccess();
}

void Acquisition::onAccessGranted(const OAuthToken& token)
{
    QLOG_INFO() << "Acquisition: OAuth access has been granted";
    m_settings->setUsername(token.username);
    m_user_data->setUsername(token.username);
    m_user_data->setStruct("oauth_token", token);
    m_rate_limiter->setToken(token);
    getLeagues();
}

void Acquisition::openLogFile()
{
    QUrl settings_url("file:///" + makeLogFilename(m_data_directory), QUrl::TolerantMode);
    QLOG_DEBUG()<< "Application: opening log file:" << settings_url.toString();
    QDesktopServices::openUrl(settings_url);
}

void Acquisition::restoreDefaultLogLevel()
{
    const auto& default_level = DEFAULT_LOGGING_LEVEL;
    QLOG_DEBUG() << "Acquisition: restoring default logging level:" << utils::loggingLevelName(default_level);
    if (m_settings->loggingLevel() == default_level) {
        return;
    };
    m_settings->setLoggingLevel(default_level);
    for (auto& action : m_logging_actions) {
        action->setChecked(action->data() == default_level);
    };
}

void Acquisition::setLeague()
{
    for (const auto action : m_league_actions) {
        if (action->isChecked()) {
            const QString league = action->data().toString();
            QLOG_DEBUG() << "Acquisition: setting the league to" << league;
            m_settings->setLeague(league);
            return;
        };
    };
    QLOG_WARN() << "Acquisition: unable to set the league";
}


void Acquisition::setLoggingLevel()
{
    for (const auto action : m_logging_actions) {
        if (action->isChecked()) {
            const QsLogging::Level level = static_cast<QsLogging::Level>(action->data().toInt());
            QLOG_DEBUG() << "Acquisition: setting the logging level to" << utils::loggingLevelName(level);
            m_settings->setLoggingLevel(level);
            return;
        };
    };
    QLOG_WARN() << "Acquisition: unable to set the logging level";
}

void Acquisition::refreshCharacterIndex()
{
    QLOG_DEBUG() << "Acquisition: refreshing character index";
};

void Acquisition::refreshStashIndex()
{
    QLOG_DEBUG() << "Acquisition: refreshing stash index";
};

void Acquisition::refreshAllIndexes()
{
    QLOG_DEBUG() << "Acquisition: refreshing character and stash indexes";
};

void Acquisition::refreshCharacters()
{
    QLOG_DEBUG() << "Acquisition: refreshing characters";
};

void Acquisition::refreshStashes()
{
    QLOG_DEBUG() << "Acquisition: refreshing stashes";
};

void Acquisition::refreshCharactersAndStashes()
{
    QLOG_DEBUG() << "Acquisition: refreshing characters and stashes";
};

void Acquisition::refreshEverything()
{
    QUrl url;
    QNetworkRequest request;
    RateLimitedReply* reply;

    QLOG_DEBUG() << "Acquisition: refreshing everything";
    url = QUrl(SERVER_ENDPOINT "/character");
    request = QNetworkRequest(url);
    QLOG_TRACE() << "Acquisition: requesting character list";
    reply = m_rate_limiter->Submit("LIST_CHARACTERS", request);
    connect(reply, &RateLimitedReply::finished, this, &Acquisition::refreshEverything_characterListReceived);

    const QString league = m_settings->league();
    QLOG_TRACE() << "Acquisition: listing stashes for" << league;
    url = QUrl(SERVER_ENDPOINT "/stash/" + league);
    request = QNetworkRequest(url);
    reply = m_rate_limiter->Submit("LIST_STASHES", request);
    connect(reply, &RateLimitedReply::finished, this, &Acquisition::refreshEverything_stashListReceived);
};

void Acquisition::refreshEverything_characterListReceived(QNetworkReply* reply)
{
    QLOG_TRACE() << "Acquisition: received character list";
    const QString league = m_settings->league();
    const auto payload = utils::parse_json<poe_api::CharacterListWrapper>(reply->readAll());
    reply->deleteLater();
    m_characters = std::move(payload->characters);

    QStringList names;
    for (const auto& character : *m_characters) {
        if (m_settings->league() == character->league.value_or("")) {
            names.append(character->name);
        };
    };

    QLOG_TRACE() << "Acquisition: requesting" << names.size() << "characters in" << league;
    for (int i = 0; i < names.size(); ++i) {
        const QString& name = names[i];
        QLOG_TRACE() << "Acquisition: requesting character" << i << "of" << names.size() << ":" << name;
        const QUrl url(SERVER_ENDPOINT "/character/" + name);
        const QNetworkRequest request(url);
        auto* reply = m_rate_limiter->Submit("GET_CHARACTER", request);
        connect(reply, &RateLimitedReply::finished, this, &Acquisition::refreshEverything_characterReceived);
    };
};

void Acquisition::refreshEverything_characterReceived(QNetworkReply* reply)
{
    auto payload = utils::parse_json<poe_api::CharacterWrapper>(reply->readAll());
    reply->deleteLater();
    m_league_data->storeCharacter(*payload->character);
    for (auto& character : *m_characters) {
        if (character->name == payload->character->name) {
            character = std::move(payload->character);
        };
    };
};

void Acquisition::refreshEverything_stashListReceived(QNetworkReply* reply)
{
    const QString league = m_settings->league();
    const auto payload = utils::parse_json<poe_api::StashListWrapper>(reply->readAll());
    reply->deleteLater();
    m_stashes = std::move(payload->stashes);

    for (size_t i = 0; i < m_stashes->size(); ++i) {
        const poe_api::StashTab& stash = *(*m_stashes)[i];
        if (stash.parent) {

        };'
        const QString& stash_id = stash.id;
        //const QString& substash_id = stash.parent;
        QLOG_TRACE() << "Acquisition: getting stash" << i << "of" << m_stashes->size() << "in" << league + ":" << stash_id << substash_id;
        const QString stash_location = stash_id + ((substash_id.isEmpty()) ? "" : "/" + substash_id);
        const QUrl url(SERVER_ENDPOINT "/stash/" + league + "/" + stash_location);
        const QNetworkRequest request(url);
        auto* reply = m_rate_limiter->Submit("GET_STASH", request);
        connect(reply, &RateLimitedReply::finished, this, [](){});
    };
};

void Acquisition::refreshEverything_stashReceived(QNetworkReply* reply)
{
    auto payload = utils::parse_json<poe_api::StashWrapper>(reply->readAll());
    reply->deleteLater();
    for (auto& stash : *m_stashes) {
        if (stash->id == payload->stash->id) {
            stash = std::move(payload->stash);
        };
    };
};


void Acquisition::getLeagues()
{
    QLOG_TRACE() << "Acquisition: requesting leagues";
    const QUrl url(SERVER_ENDPOINT "/account/leagues");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_LEAGUES", request);
    connect(reply, &RateLimitedReply::finished, this,
        [this](QNetworkReply* reply) {
            QString current_league = m_settings->league();
            const auto data = reply->readAll();
            const auto payload = utils::parse_json<poe_api::LeagueListWrapper>(data);
            if (current_league.isEmpty()) {
                current_league = (*payload->leagues).front()->id;
                m_settings->setLeague(current_league);
            };
            m_league_actions.clear();
            m_league_actions.reserve(payload->leagues->size());
            for (const auto& league : *payload->leagues) {
                const QString display_name = utils::leaguePrettyName(league->id);
                QAction* action = new QAction(display_name, this);
                action->setCheckable(true);
                action->setChecked(league->id == current_league);
                action->setData(league->id);
                connect(action, &QAction::triggered, this, &Acquisition::setLeague);
                m_league_actions.append(action);
            };
            emit leagueListChanged();
        });
}

void Acquisition::listCharacters()
{
    QLOG_TRACE() << "Acquisition: requesting character list";
    const QUrl url(SERVER_ENDPOINT "/character");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("LIST_CHARACTERS", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            const auto payload = utils::parse_json<poe_api::CharacterListWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Acquisition::getCharacter(
    const QString& name)
{
    QLOG_TRACE() << "Acquisition: requesting character" << name;
    const QUrl url(SERVER_ENDPOINT "/character/" + name);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_CHARACTER", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::CharacterWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Acquisition::listStashes(
    const QString& league)
{
    QLOG_TRACE() << "Acquisition: listing stashes for" << league;
    const QUrl url(SERVER_ENDPOINT "/stash/" + league);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("LIST_STASHES", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::StashListWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Acquisition::getStash(
    const QString& league,
    const QString& stash_id,
    const QString& substash_id)
{
    QLOG_TRACE() << "Acquisition: getting stash in" << league + ":" << stash_id << substash_id;
    const QString stash_location = stash_id + ((substash_id.isEmpty()) ? "" : "/" + substash_id);
    const QUrl url(SERVER_ENDPOINT "/stash/" + league + "/" + stash_location);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_STASH", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::StashWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Acquisition::setMinLevel(double value)
{
    if (std::isnan(value)) {
        m_proxy_model->removeFilter("MIN_LEVEL");
    } else {
        m_proxy_model->setFilter("MIN_LEVEL",
            [value](const poe_api::Item& item) {
                if (!item.requirements) {
                    return true;
                };
                //auto& requirements = item.requirements.value();
            });
    };
}

void Acquisition::setMaxLevel(double  value)
{

}
