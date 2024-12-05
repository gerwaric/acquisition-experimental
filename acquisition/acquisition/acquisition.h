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

class QNetworkAccessManager;

class LeagueDataStore;
class OAuthManager;
class RateLimiter;
class Settings;
class UserDataStore;

class Acquisition : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(bool authenticated MEMBER m_authenticated NETIFY authenticationStatusChanged)
    Q_PROPERTY(QString statusText MEMBER m_status_text NOTIFY statusChanged)
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
    void authenticationStatusChanged();
    void leagueListChanged();
    void leagueChanged();
    void treeModelChanged();
    void searchResultsChanged();
    void statusChanged();

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
    void refreshEverything_stashListReceived(QNetworkReply* reply);

	void getLeagues();

private:
    void loadSettings();
    void initLeagueActions();
    void initLoggingActions();

    void updateCharacter(std::unique_ptr<poe_api::Character>& character);
    void updateStash(std::unique_ptr<poe_api::StashTab>& stash);

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

    QString m_status_text{ "Status" };
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

    poe_api::CharacterList m_characters;
    poe_api::StashTabList m_stashes;

    bool m_authenticated{ false };

    size_t m_characters_requested{ 0 };
    size_t m_characters_received{ 0 };

    size_t m_stashes_requested{ 0 };
    size_t m_stashes_received{ 0 };

    void updateStatus();

};
