#include <acquisition.h>

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/command_line.h>
#include <acquisition/constants.h>
#include <acquisition/data_stores/league_data_store.h>
#include <acquisition/data_stores/user_data_store.h>
#include <acquisition/oauth/oauth_manager.h>
#include <acquisition/rate_limit/rate_limiter.h>
#include <acquisition/settings.h>
#include <acquisition/utils/json.h>

#include <QsLog/QsLog.h>

#include <QDesktopServices>
#include <QDir>

#define SERVER_ENDPOINT "https://api.pathofexile.com"

const OAuthSettings Acquisition::s_oauth_settings = {
    "https://www.pathofexile.com/oauth/authorize",
    "https://www.pathofexile.com/oauth/token",
    "acquisition",
    "account:leagues account:stashes account:characters",
    "http://127.0.0.1",
    "/auth/path-of-exile"
};

Acquisition::Acquisition(QObject* parent) : QObject(parent)
{
    const QString banner_text("- Starting " APP_NAME " version " APP_VERSION_STRING " -");
    const QString banner_line(banner_text.length(), '-');

    QLOG_INFO() << banner_line;
    QLOG_INFO() << banner_text;
    QLOG_INFO() << banner_line;

    m_network_manager = new QNetworkAccessManager(this);
    m_oauth_manager = new OAuthManager(*m_network_manager, s_oauth_settings, this);
    m_rate_limiter = new RateLimiter(*m_network_manager, this);
    m_tree_model = new TreeModel(this);

    connect(m_oauth_manager, &OAuthManager::accessGranted, this, &Acquisition::onAccessGranted);
}

void Acquisition::init(const QString& directory)
{
    QLOG_DEBUG() << "Acquisition: loading settings and data from" << directory;
    m_settings = new Settings(directory, this);

    QLOG_DEBUG() << "Acquisition: loading user database";
    m_user_data = new UserDataStore(directory, this);

    QLOG_DEBUG() << "Acquisition: loading league database";
    m_league_data = new LeagueDataStore(directory, this);

    loadSettings();
    initLeagueMenu();
    initRefreshMenu();
    initLoggingMenu();
}

QString Acquisition::makeLogFilename(const QString& directory)
{
    return directory + QDir::separator() + "log-new.txt";
}

void Acquisition::loadSettings()
{
    QLOG_DEBUG() << "Acquisition: loading application settings";

    if (!m_settings->username().isEmpty()) {
        const QString username = m_settings->username();
        QLOG_DEBUG() << "Acquisition: username is" << username;
        m_user_data->setUsername(username);
        m_league_data->setUsername(username);
    };

    if (!m_settings->league().isEmpty()) {
        const QString league = m_settings->league();
        QLOG_DEBUG() << "Acquisition: league is" << league;
        m_league_data->setLeague(league);
    };

    int i;

    QLOG_DEBUG() << "Acquisition: loading stored characters";
    m_characters = m_league_data->getCharacters();
    i = 0;
    for (auto& character : m_characters) {
        QLOG_TRACE() << "Acquisition: loading character" << ++i << character->name;
        m_tree_model->appendCharacter(*character);
    };

    QLOG_DEBUG() << "Application: loading stored stashes";
    m_stashes = m_league_data->getStashes();
    i = 0;
    for (auto& stash : m_stashes) {
        QLOG_TRACE() << "Application: loading stash" << ++i << stash->type + ":" << stash->name;
        m_tree_model->appendStash(*stash);
    };

    emit treeModelChanged();

    OAuthToken token = m_user_data->getStruct<OAuthToken>("oauth_token");
    if (token.isValid()) {
        m_oauth_manager->setToken(token);
    };

}

void Acquisition::initLeagueMenu()
{
    QLOG_DEBUG() << "Acquisition: initializing the league menu actions";
    const QString current_league = m_settings->league();
    if (!current_league.isEmpty()) {
        QAction* action = new QAction(current_league, this);
        action->setCheckable(true);
        action->setChecked(true);
        m_league_actions = { action };
    };
    emit leagueListChanged();
}

void Acquisition::initRefreshMenu()
{
    QLOG_DEBUG() << "Acquisition: initializing the refresh menu actions";
    m_refresh_actions = {};
}

void Acquisition::initLoggingMenu()
{
    QLOG_DEBUG() << "Acquisition: initializing the logging menu actions";
    const QsLogging::Level current_logging_level = m_settings->loggingLevel();

    m_logging_actions.clear();
    m_logging_actions.reserve(utils::logging_level_names.size());
    for (const auto& pair : utils::logging_level_names) {
        const QsLogging::Level level = pair.first;
        const char* name = pair.second;
        QAction* action = new QAction(name, this);
        action->setCheckable(true);
        action->setChecked(level == current_logging_level);
        action->setData(level);
        connect(action, &QAction::triggered, this, [=]() { setLoggingLevel(level); });
        m_logging_actions.append(action);
    };
}

void Acquisition::authenticate()
{
    m_oauth_manager->requestAccess();
}

void Acquisition::onAccessGranted(const OAuthToken& token)
{
    QLOG_INFO() << "Acquisition: OAuth access granted";
    m_settings->setUsername(token.username);
    m_user_data->setUsername(token.username);
    m_user_data->setStruct("oauth_token", token);
    m_rate_limiter->setToken(token);
    getLeagues();
}

void Acquisition::openLogFile()
{
    QUrl settings_url("file:///" + makeLogFilename(m_data_directory), QUrl::TolerantMode);
    QLOG_DEBUG()<< "Application: opening log from" << settings_url.toString();
    QDesktopServices::openUrl(settings_url);
}

void Acquisition::restoreDefaultLogLevel()
{
    if (m_settings->loggingLevel() == DEFAULT_LOGGING_LEVEL) {
        return;
    };
    m_settings->setLoggingLevel(DEFAULT_LOGGING_LEVEL);
    for (auto& action : m_logging_actions) {
        action->setChecked(action->data() == DEFAULT_LOGGING_LEVEL);
    };
}

void Acquisition::setLoggingLevel(QsLogging::Level level)
{
    QLOG_DEBUG() << "Acquisition: setting the logging level to" << level;
    for (const auto action : m_logging_actions) {
        const auto action_level = static_cast<QsLogging::Level>(action->data().toInt());
        action->setChecked(action_level == level);
    };
    m_settings->setLoggingLevel(level);
}

void Acquisition::getLeagues()
{
    QLOG_TRACE() << "Acquisition: requesting leagues";
    const QUrl url(SERVER_ENDPOINT "/account/leagues");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_LEAGUES", request);
    connect(reply, &RateLimitedReply::finished, this,
        [this](QNetworkReply* reply) {
            const auto data = reply->readAll();
            auto payload = utils::parse_json<poe_api::LeagueListWrapper>(data);
            const QString current_league_id = m_settings->league();
            m_league_actions.clear();
            m_league_actions.reserve(payload->leagues->size());
            for (const auto& league : *payload->leagues) {
                QAction* action = new QAction(league->id, this);
                action->setCheckable(true);
                action->setChecked(league->id == current_league_id);
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
            auto payload = utils::parse_json<poe_api::CharacterListWrapper>(reply->readAll());
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

