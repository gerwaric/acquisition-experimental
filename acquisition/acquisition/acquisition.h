#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/data_model/tree_model.h>
#include <acquisition/oauth/oauth_token.h>
#include <acquisition/proxy_model.h>
#include <acquisition/settings.h>
#include <acquisition/search_filters.h>

#include <QObject>
#include <QQmlEngine>

#include <QAbstractItemModel>
#include <QAction>
#include <QList>
#include <QSortFilterProxyModel>
#include <QString>
#include <QStringList>

#include <vector>

class QNetworkAccessManager;

class LeagueDataStore;
class OAuthManager;
class RateLimiter;
class Settings;
class UserDataStore;

class Acquisition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QAction*> leagueActions MEMBER m_league_actions NOTIFY leagueListChanged)
    Q_PROPERTY(QList<QAction*> loggingActions MEMBER m_logging_actions CONSTANT)
    Q_PROPERTY(QAbstractItemModel* treeModel READ treeModel NOTIFY treeModelChanged)
    Q_PROPERTY(QSortFilterProxyModel* searchResultsModel READ searchResultsModel NOTIFY searchResultsChanged)
    Q_PROPERTY(SearchFilters* searchFilters MEMBER m_search_filters CONSTANT)
    QML_ELEMENT
    QML_SINGLETON

public:
    Acquisition(QObject* parent = nullptr);

    void setDataDirectory(const QString& directory);

    QAbstractItemModel* treeModel() { return m_tree_model; };
    QSortFilterProxyModel* searchResultsModel() { return m_proxy_model; };

    static QString makeLogFilename(const QString& directory);

signals:
    void leagueListChanged();
    void leagueChanged();
    void treeModelChanged();
    void searchResultsChanged();

public slots:
    void authenticate();
    void openLogFile();
    void restoreDefaultLogLevel();
    void onAccessGranted(const OAuthToken& token);

    void refreshCharacterIndex();
    void refreshStashIndex();
    void refreshAllIndexes();
    void refreshCharacters();
    void refreshStashes();
    void refreshCharactersAndStashes();

    void refreshEverything();
    void refreshEverything_characterListReceived(QNetworkReply* reply);
    void refreshEverything_characterReceived(QNetworkReply* reply);
    void refreshEverything_stashListReceived(QNetworkReply* reply);
    void refreshEverything_stashReceived(QNetworkReply* reply);

    void setMinLevel(double value);
    void setMaxLevel(double value);

private:
    void loadSettings();
    void initLeagueActions();
    void initLoggingActions();

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

    void setLeague();
    void setLoggingLevel();

    QStringList m_logging_levels;

    QNetworkAccessManager* m_network_manager{ nullptr };

    OAuthManager* m_oauth_manager{ nullptr };
    RateLimiter* m_rate_limiter{ nullptr };
    TreeModel* m_tree_model{ nullptr };
    ProxyModel* m_proxy_model{ nullptr };
    SearchFilters* m_search_filters{ nullptr };

    QString m_data_directory;
    Settings* m_settings{ nullptr };
    UserDataStore* m_user_data{ nullptr };
    LeagueDataStore* m_league_data{ nullptr };

    QList<QAction*> m_league_actions;
    QList<QAction*> m_refresh_actions;
    QList<QAction*> m_logging_actions;

    std::unique_ptr<poe_api::CharacterList> m_characters;
    std::unique_ptr<poe_api::StashTabList> m_stashes;
};
