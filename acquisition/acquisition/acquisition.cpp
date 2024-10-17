#include <acquisition/acquisition.h>

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/data_stores/league_data_store.h>
#include <acquisition/data_stores/user_data_store.h>
#include <acquisition/oauth/oauth_manager.h>
#include <acquisition/oauth/oauth_settings.h>
#include <acquisition/oauth/oauth_token.h>
#include <acquisition/rate_limit/rate_limiter.h>
#include <acquisition/settings.h>
#include <acquisition/utils/json.h>

#include <QsLog/QsLog.h>

#include <QDesktopServices>
#include <QDir>

#define SERVER_ENDPOINT "https://api.pathofexile.com"

const OAuthSettings Application::s_oauth_settings = {
    "https://www.pathofexile.com/oauth/authorize",
    "https://www.pathofexile.com/oauth/token",
    "acquisition",
    "account:leagues account:stashes account:characters",
    "http://127.0.0.1",
    "/auth/path-of-exile"
};

Application::Application(const QString& data_directory, QObject* parent)
    : QObject(parent)
    , m_data_directory(data_directory)
{
    QLOG_DEBUG() << "Application: setting up the application using data in" << data_directory;

    m_network_manager = new QNetworkAccessManager(this);
    m_oauth_manager = new OAuthManager(this, *m_network_manager, s_oauth_settings);
    m_rate_limiter = new RateLimiter(this, *m_network_manager);
    m_tree_model = new TreeModel(this);

    connect(m_oauth_manager, &OAuthManager::accessGranted, this, &Application::onAccessGranted);
    //connect(this, &Application::leagueListReceived, this, &Application::updateLeagueList);

    QLOG_DEBUG() << "Application: loading settings";
    m_settings = new Settings(this, data_directory);

    QLOG_DEBUG() << "Application: loading user data";
    m_user_data = new UserDataStore(this, data_directory);

    QLOG_DEBUG() << "Application: loading league data";
    m_league_data = new LeagueDataStore(this, data_directory);

    loadSettings();
    initLeagueMenuActions();
    initLoggingMenuActions();
}

QString Application::makeLogFilename(const QString& directory)
{
    return directory + QDir::separator() + "log-new.txt";
}

void Application::loadSettings()
{
    QLOG_DEBUG() << "Application: loading application settings";

    if (!m_settings->username().isEmpty()) {
        const QString username = m_settings->username();
        QLOG_DEBUG() << "Application: username is" << username;
        m_user_data->setUsername(username);
        m_league_data->setUsername(username);
    };

    if (!m_settings->league().isEmpty()) {
        const QString league = m_settings->league();
        QLOG_DEBUG() << "Application: league is" << league;
        m_league_data->setLeague(league);
    };

    int i;

    QLOG_DEBUG() << "Application: loading stored characters";
    m_characters = m_league_data->getCharacters();
    i = 0;
    for (auto& character : m_characters) {
        QLOG_TRACE() << "Application: loading character" << ++i << character->name;
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
}

void Application::initLeagueMenuActions()
{
    QLOG_DEBUG() << "Application: initializing the league menu";
    const QString current_league = m_settings->league();
    if (!current_league.isEmpty()) {
        QAction* action = new QAction(current_league, this);
        action->setCheckable(true);
        action->setChecked(true);
        m_league_menu_actions = { action };
    };
}

void Application::initLoggingMenuActions()
{
    QLOG_DEBUG() << "Application: initializing the logging menu";
    const QsLogging::Level current_logging_level = m_settings->logLevel();

    constexpr std::array logging_action_setup = {
        std::make_pair("Off", QsLogging::OffLevel),
        std::make_pair("Fatal", QsLogging::FatalLevel),
        std::make_pair("Error", QsLogging::ErrorLevel),
        std::make_pair("Warn", QsLogging::WarnLevel),
        std::make_pair("Info (recommended)", QsLogging::InfoLevel),
        std::make_pair("Debug", QsLogging::DebugLevel),
        std::make_pair("Trace", QsLogging::TraceLevel)
    };

    m_logging_menu_actions.clear();
    m_logging_menu_actions.reserve(logging_action_setup.size());
    for (const auto& pair : logging_action_setup) {
        const char* name = pair.first;
        const QsLogging::Level level = pair.second;
        QAction* action = new QAction(name, this);
        action->setCheckable(true);
        action->setChecked(level == current_logging_level);
        action->setData(level);
        connect(action, &QAction::triggered, this, [=]() { setLoggingLevel(level); });
        m_logging_menu_actions.append(action);
    };
}

void Application::authenticate()
{
    m_oauth_manager->requestAccess();
}

void Application::onAccessGranted(const OAuthToken& token)
{
    QLOG_INFO() << "Application: OAuth access granted";
    m_settings->setUsername(token.username);
    m_user_data->setUsername(token.username);
    m_user_data->setStruct("oauth_token", token);
    m_rate_limiter->setToken(token);
    getLeagues();
}

void Application::openLogFile()
{
    QUrl settings_url("file:///" + makeLogFilename(m_data_directory), QUrl::TolerantMode);
    QLOG_DEBUG()<< "Application: opening log from" << settings_url.toString();
    QDesktopServices::openUrl(settings_url);
}

void Application::setLoggingLevel(QsLogging::Level level)
{
    QLOG_DEBUG() << "Application: setting the logging level to" << level;
    for (const auto action : m_logging_menu_actions) {
        const auto action_level = static_cast<QsLogging::Level>(action->data().toInt());
        action->setChecked(action_level == level);
    };
    m_settings->setLogLevel(level);
}

void Application::getLeagues()
{
    QLOG_TRACE() << "Application: requesting leagues";
    const QUrl url(SERVER_ENDPOINT "/account/leagues");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_LEAGUES", request);
    connect(reply, &RateLimitedReply::finished, this,
        [this](QNetworkReply* reply) {
            const auto data = reply->readAll();
            auto payload = utils::parse_json<poe_api::LeagueListWrapper>(data);
            m_league_menu_actions.clear();
            m_league_menu_actions.reserve(payload->leagues->size());
            for (const auto& league : *payload->leagues) {
                QAction* action = new QAction(league->id, this);
                action->setCheckable(true);
                action->setChecked(false);
                m_league_menu_actions.append(action);
            };
            emit leagueListChanged();
        });
}

void Application::listCharacters()
{
    QLOG_TRACE() << "Application: requesting character list";
    const QUrl url(SERVER_ENDPOINT "/character");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("LIST_CHARACTERS", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::CharacterListWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Application::getCharacter(
    const QString& name)
{
    QLOG_TRACE() << "Application: requesting character" << name;
    const QUrl url(SERVER_ENDPOINT "/character/" + name);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("GET_CHARACTER", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::CharacterWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Application::listStashes(
    const QString& league)
{
    QLOG_TRACE() << "Application: listing stashes for" << league;
    const QUrl url(SERVER_ENDPOINT "/stash/" + league);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter->Submit("LIST_STASHES", request);
    connect(reply, &RateLimitedReply::finished, this,
        [](QNetworkReply* reply) {
            auto payload = utils::parse_json<poe_api::StashListWrapper>(reply->readAll());
            reply->deleteLater();
        });
}

void Application::getStash(
    const QString& league,
    const QString& stash_id,
    const QString& substash_id)
{
    QLOG_TRACE() << "Application: getting stash in" << league + ":" << stash_id << substash_id;
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

