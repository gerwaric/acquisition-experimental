#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/oauth/oauth_settings.h>
#include <acquisition/data_model/tree_model.h>

#include <QObject>

#include <QAbstractItemModel>
#include <QAction>
#include <QList>
#include <QString>
#include <QStringList>

#include <vector>

class QNetworkAccessManager;

class LeagueDataStore;
class OAuthManager;
class OAuthToken;
class RateLimiter;
class Settings;
class UserDataStore;

class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QAction*> leagueMenuActions MEMBER m_league_menu_actions NOTIFY leagueListChanged)
    Q_PROPERTY(QList<QAction*> loggingMenuActions MEMBER m_logging_menu_actions CONSTANT)
    Q_PROPERTY(QAbstractItemModel* treeModel READ treeModel NOTIFY treeModelChanged)

public:
    Application(const QString& data_directory, QObject* parent = nullptr);

    QAbstractItemModel* treeModel() { return m_tree_model; };

    static QString makeLogFilename(const QString& directory);

signals:
    void leagueListChanged();
    void leagueChanged();
    void treeModelChanged();

public slots:
    void authenticate();
    void openLogFile();
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
    void initLeagueMenuActions();
    void initLoggingMenuActions();


    void setLoggingLevel(QsLogging::Level level);

    static const OAuthSettings s_oauth_settings;

    const QString m_data_directory;

    QNetworkAccessManager* m_network_manager;

    Settings* m_settings{ nullptr };
    OAuthManager* m_oauth_manager{ nullptr };
    RateLimiter* m_rate_limiter{ nullptr };
    TreeModel* m_tree_model{ nullptr };
    UserDataStore* m_user_data{ nullptr };
    LeagueDataStore* m_league_data{ nullptr };

    QList<QAction*> m_league_menu_actions;
    QList<QAction*> m_logging_menu_actions;

    std::vector<std::shared_ptr<poe_api::Character>> m_characters;
    std::vector<std::shared_ptr<poe_api::StashTab>> m_stashes;

};
