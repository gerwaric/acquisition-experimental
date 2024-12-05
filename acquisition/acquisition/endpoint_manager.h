#pragma once

#include <acquisition/api_types/account_profile.h>
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

public slots:

    void getProfile();

    void getLeagues(
        const QString& realm);

    void listCharacters(
        const QString& realm);
        
    void getCharacter(
        const QString& realm,
        const QString& name);

    void listStashes(
        const QString& realm,
        const QString& league);

    void getStash(
        const QString& realm,
        const QString& league,
        const QString& stash_id,
        const QString& substash_id = "");

signals:

    void profileReceived(const poe_api::AccoutProfile& profile);
    void leagueListReceived(const std::vector<poe_api::League>& leagues);
    void characterListReceived(std::vector<std::shared_ptr<poe_api::Character>> characters);
    void characterReceived(std::shared_ptr<poe_api::Character> character);
    void stashListReceived(std::vector<std::shared_ptr<poe_api::StashTab>> stashes);
    void stashReceived(std::shared_ptr<poe_api::StashTab> stash);

private slots:
        
    void receiveProfile(QNetworkReply* reply);
    void receiveLeagueList(QNetworkReply* reply);
    void receiveCharacterList(QNetworkReply* reply);
    void receiveCharacter(QNetworkReply* reply);
    void receiveStashList(QNetworkReply* reply);
    void receiveStash(QNetworkReply* reply);

private:

    RateLimiter& m_rate_limiter;

};
