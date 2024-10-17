#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/league.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/data_model/tree_model.h>

#include <QObject>

#include <QNetworkReply>
#include <QString>

//#include <optional>
//#include <string>
#include <unordered_map>
#include <vector>

class RateLimiter;

class EndpointManager : public QObject {
    Q_OBJECT
    
public:

    explicit EndpointManager(QObject* parent, RateLimiter& rate_limiter);

    std::unique_ptr<std::vector<poe_api::League>> getLeagueList();
    std::unique_ptr<std::vector<poe_api::Character>> getCharacters();
    std::unique_ptr<std::vector<poe_api::StashTab>> getStashes();

    void characterReceived(std::shared_ptr<poe_api::Character> character);
    void stashListReceived(std::vector<std::shared_ptr<poe_api::StashTab>> stashes);
    void stashReceived(std::shared_ptr<poe_api::StashTab> stash);

public slots:

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

signals:

    void leagueListReceived(const std::vector<poe_api::League>& leagues);
    void characterListReceived(std::vector<std::shared_ptr<poe_api::Character>> characters);
    void characterReceived(std::shared_ptr<poe_api::Character> character);
    void stashListReceived(std::vector<std::shared_ptr<poe_api::StashTab>> stashes);
    void stashReceived(std::shared_ptr<poe_api::StashTab> stash);

private slots:
        
    void receiveLeagueList(QNetworkReply* reply);
    void receiveCharacterList(QNetworkReply* reply);
    void receiveCharacter(QNetworkReply* reply);
    void receiveStashList(QNetworkReply* reply);
    void receiveStash(QNetworkReply* reply);

private:

    RateLimiter& m_rate_limiter;

};
