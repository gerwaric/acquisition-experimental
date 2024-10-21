#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/oauth/oauth_settings.h>
#include <acquisition/oauth/oauth_token.h>
#include <acquisition/data_model/tree_model.h>

#include <QObject>
//#include <QQmlEngine>

#include <QAbstractItemModel>
#include <QAction>
#include <QList>
#include <QString>
#include <QStringList>

#include <vector>

class QNetworkAccessManager;

class LeagueDataStore;
class OAuthManager;
class RateLimiter;
class Settings;
class UserDataStore;

#include <acquisition/settings.h>

class Acquisition : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QList<QAction*> leagueActions MEMBER m_league_actions NOTIFY leagueListChanged)
    //Q_PROPERTY(QList<QAction*> refreshActions MEMBER m_refresh_actions CONSTANT)
    //Q_PROPERTY(QList<QAction*> loggingActions MEMBER m_logging_actions CONSTANT)
    //Q_PROPERTY(QAbstractItemModel* treeModel READ treeModel NOTIFY treeModelChanged)
    //QML_ELEMENT
    //QML_SINGLETON

public:
    Acquisition(QObject* parent = nullptr);

    void init(const QString& directory);

    QAbstractItemModel* treeModel() { return m_tree_model; };

    static QString makeLogFilename(const QString& directory);

signals:
    void leagueListChanged();
    void leagueChanged();
    void treeModelChanged();

public slots:
    void authenticate();
    void openLogFile();
    void restoreDefaultLogLevel();
    void onAccessGranted(const OAuthToken& token);

    void getLeagues();
    void listCharacters();
    void getCharacter(
        const QString& name);
    void listStashes(
        const QString& league);
    void getStash(
        const QString& league,
        const QString& stash_id,
        const QString& substash_id = "");

private:
    void loadSettings();
    void initLeagueMenu();
    void initRefreshMenu();
    void initLoggingMenu();

    QStringList m_logging_levels;
    void loggingLevelChanged(int index);

    void setLoggingLevel(QsLogging::Level level);

    static const OAuthSettings s_oauth_settings;

    QNetworkAccessManager* m_network_manager;

    OAuthManager* m_oauth_manager{ nullptr };
    RateLimiter* m_rate_limiter{ nullptr };
    TreeModel* m_tree_model{ nullptr };

    QString m_data_directory;
    Settings* m_settings{ nullptr };
    UserDataStore* m_user_data{ nullptr };
    LeagueDataStore* m_league_data{ nullptr };

    QList<QAction*> m_league_actions;
    QList<QAction*> m_refresh_actions;
    QList<QAction*> m_logging_actions;

    std::vector<std::shared_ptr<poe_api::Character>> m_characters;
    std::vector<std::shared_ptr<poe_api::StashTab>> m_stashes;

};
