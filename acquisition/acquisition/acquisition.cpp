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
    QLOG_DEBUG() << "Acquisition: loading" << m_characters.size() << "stored characters";
    for (size_t i = 0; i < m_characters.size(); ++i) {
        const poe_api::Character& character = *m_characters[i];
        QLOG_TRACE() << "Acquisition: loading character" << i << "/" << m_characters.size() << character.name;
        m_tree_model->appendCharacter(character);
    }

    m_stashes = m_league_data->getStashes();
    QLOG_DEBUG() << "Application: loading" << m_stashes.size() << "stored stashes";
    for (size_t i = 0; i < m_stashes.size(); ++i) {
        const poe_api::StashTab& stash = *m_stashes[i];
        QLOG_TRACE() << "Application: loading stash" << i << "/" << m_stashes.size() << stash.type + ":" << stash.name;
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
    m_authenticated = true;
    emit authenticationStatusChanged();
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
    m_characters_requested = 0;
    m_characters_received = 0;

    const QUrl url(SERVER_ENDPOINT "/character");
    const QNetworkRequest request(url);
    QLOG_TRACE() << "Acquisition: requesting character list";
    RateLimitedReply* reply = m_rate_limiter->Submit("LIST_CHARACTERS", request);
    connect(reply, &RateLimitedReply::finished, this, &Acquisition::refreshEverything_characterListReceived);
};

void Acquisition::refreshStashes()
{
    QLOG_DEBUG() << "Acquisition: refreshing stashes";
    m_stashes_requested = 0;
    m_stashes_received = 0;

    const QString league = m_settings->league();
    QLOG_TRACE() << "Acquisition: listing stashes for" << league;
    const QUrl url(SERVER_ENDPOINT "/stash/" + league);
    const QNetworkRequest request(url);
    RateLimitedReply* reply = m_rate_limiter->Submit("LIST_STASHES", request);
    connect(reply, &RateLimitedReply::finished, this, &Acquisition::refreshEverything_stashListReceived);
};

void Acquisition::refreshCharactersAndStashes()
{
    QLOG_DEBUG() << "Acquisition: refreshing characters and stashes";
};

void Acquisition::refreshEverything()
{
    QLOG_DEBUG() << "Acquisition: refreshing everything";
    refreshCharacters();
    refreshStashes();
};

void Acquisition::refreshEverything_characterListReceived(QNetworkReply* reply)
{
    QLOG_TRACE() << "Acquisition: received character list";
    const QString league = m_settings->league();
    const auto payload = utils::parse_json<poe_api::CharacterListWrapper>(reply->readAll());
    reply->deleteLater();

    m_characters.clear();
    m_characters.reserve(payload->characters.size());
    for (auto& character : payload->characters) {
        if (league == character->league.value_or("")) {
            m_characters.push_back(std::move(character));
        };
    };
    m_characters.shrink_to_fit();
    m_characters_requested += m_characters.size();
    updateStatus();

    for (auto& character : m_characters) {
        updateCharacter(character);
    };
};

void Acquisition::updateCharacter(std::unique_ptr<poe_api::Character>& character)
{
    const QString& name = character->name;
    QLOG_TRACE() << "Acquisition: updating character:" << name;
    const QUrl url(SERVER_ENDPOINT "/character/" + name);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_CHARACTER", request);
    connect(reply, &RateLimitedReply::finished, this,
        [&](QNetworkReply* reply) {
            ++m_characters_received;
            const auto bytes(reply->readAll());
            const auto payload = utils::parse_json<poe_api::CharacterWrapper>(bytes);
            reply->deleteLater();
            if (!payload->character) {
                QLOG_ERROR() << "Acquisition: recieved empty character";
                return;
            };
            *character = payload->character.value();
            m_league_data->storeCharacter(*character);
            updateStatus();
        });
}

void Acquisition::refreshEverything_stashListReceived(QNetworkReply* reply)
{
    const QString league = m_settings->league();
    const auto payload = utils::parse_json<poe_api::StashListWrapper>(reply->readAll());
    reply->deleteLater();

    m_stashes = std::move(payload->stashes);
    m_stashes_requested += m_stashes.size();
    updateStatus();

    for (size_t i = 0; i < m_stashes.size(); ++i) {
        updateStash(m_stashes[i]);
    };
};

void Acquisition::updateStash(std::unique_ptr<poe_api::StashTab>& stash)
{
    const QString league = m_settings->league();
    const bool has_parent = stash->parent.has_value();
    const QString stash_id = has_parent ? stash->parent.value() : stash->id;
    const QString substash_id = has_parent ? stash->id : "";
    QLOG_TRACE() << "Acquisition: getting stash in" << league + ":" << stash_id << substash_id;
    const QString stash_location = stash_id + (has_parent ? "" : "/" + substash_id);
    const QUrl url(SERVER_ENDPOINT "/stash/" + league + "/" + stash_location);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_STASH", request);
    connect(reply, &RateLimitedReply::finished, this,
        [&](QNetworkReply* reply) {
            ++m_stashes_received;
            const auto bytes = reply->readAll();
            const auto payload = utils::parse_json<poe_api::StashWrapper>(bytes);
            reply->deleteLater();
            *stash = *payload->stash;
            m_league_data->storeStash(*stash);
            updateStatus();
        });
}

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
    QLOG_DEBUG() << "Set minimum level to" << value;
    if (std::isnan(value)) {
        m_proxy_model->removeFilter(SearchFilters::Filter::LevelMin);
        return;
    };
    m_proxy_model->setFilter(SearchFilters::Filter::LevelMin,
        [value](const ItemInfo& item_info) {
            return item_info.required_level >= value;
        });
}

void Acquisition::setMaxLevel(double  value)
{
    if (std::isnan(value)) {
        m_proxy_model->removeFilter(SearchFilters::Filter::LevelMax);
        return;
    };
    m_proxy_model->setFilter(SearchFilters::Filter::LevelMax,
        [value](const ItemInfo& item_info) {
            return item_info.required_level <= value;
        });
}

void Acquisition::updateStatus()
{
    m_status_text = QString("Received %1/%2 characters and %3/%4 stashes").arg(
        QString::number(m_characters_received),
        QString::number(m_characters_requested),
        QString::number(m_stashes_received),
        QString::number(m_stashes_requested));
    emit statusChanged();
}
