#include <acquisition/endpoint_manager.h>

#include <acquisition/rate_limit/rate_limiter.h>
#include <acquisition/utils/json_struct_qt.h>

#include <QsLog/QsLog.h>

#include <QNetworkRequest>

namespace {

    struct LeagueListPayload {
        std::vector<std::shared_ptr<poe_api::League>> leagues;
        JS_OBJ(leagues);
    };

    struct CharacterListPayload {
        std::vector<std::shared_ptr<poe_api::Character>> characters;
        JS_OBJ(characters);
    };

    struct CharacterPayload {
        std::shared_ptr<poe_api::Character> character;
        JS_OBJ(character);
    };

    struct StashListPayload {
        std::vector<std::shared_ptr<poe_api::StashTab>> stashes;
        JS_OBJ(stashes);
    };

    struct StashPayload {
        std::unique_ptr<poe_api::StashTab> stash;
        JS_OBJ(stash);
    };

}

EndpointManager::EndpointManager(
    QObject* parent,
    RateLimiter& rate_limiter)
    : QObject(parent)
    , m_rate_limiter(rate_limiter) {}

void EndpointManager::getLeagues()
{
    QLOG_TRACE() << "EndpointManager::getLeagues()";
    const QUrl url("https://api.pathofexile.com/account/leagues");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter.Submit("GET_LEAGUES", request);
    connect(reply, &RateLimitedReply::finished, this, &EndpointManager::receiveLeagueList);
}

void EndpointManager::listCharacters()
{
    QLOG_TRACE() << "EndpointManager::listCharacters()";
    const QUrl url("https://api.pathofexile.com/character");
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter.Submit("LIST_CHARACTERS", request);
    connect(reply, &RateLimitedReply::finished, this, &EndpointManager::receiveCharacterList);
}

void EndpointManager::getCharacter(
    const QString& name)
{
    QLOG_TRACE() << "EndpointManager::getCharacter()" << name;
    const QUrl url("https://api.pathofexile.com/character/" + name);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter.Submit("GET_CHARACTER", request);
    connect(reply, &RateLimitedReply::finished, this, &EndpointManager::receiveCharacter);
}

void EndpointManager::listStashes(
    const QString& league)
{
    QLOG_TRACE() << "EndpointManager::listStashes()" << league;
    const QUrl url("https://api.pathofexile.com/stash/" + league);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter.Submit("LIST_STASHES", request);
    connect(reply, &RateLimitedReply::finished, this, &EndpointManager::receiveStashList);
}

void EndpointManager::getStash(
    const QString& league,
    const QString& stash_id,
    const QString& substash_id)
{
    QLOG_TRACE() << "EndpointManager::getStashes()" << league << stash_id << substash_id;
    const QString stash_location = stash_id + ((substash_id.isEmpty()) ? "" : "/" + substash_id);
    const QUrl url("https://api.pathofexile.com/stash/" + league + "/" + stash_location);
    const QNetworkRequest request(url);
    auto* reply = m_rate_limiter.Submit("GET_STASH", request);
    connect(reply, &RateLimitedReply::finished, this, &EndpointManager::receiveStash);
}

void EndpointManager::receiveLeagueList(QNetworkReply* reply)
{
    QLOG_TRACE() << "EndpointManager::receiveLeagueList()";
    LeagueListPayload payload;
    const QByteArray bytes = reply->readAll();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(payload) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing character list payload:" << parseContext.makeErrorString();
        payload.leagues = {};
    };
    emit leagueListReceived(*payload.leagues);
}

void EndpointManager::receiveCharacterList(QNetworkReply* reply)
{
    QLOG_TRACE() << "EndpointManager::receiveCharacterList()";
    CharacterListPayload payload;
    const QByteArray bytes = reply->readAll();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(payload) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing character list payload:" << parseContext.makeErrorString();
        payload.characters = {};
    };
    emit characterListReceived({});
}

void EndpointManager::receiveCharacter(QNetworkReply* reply)
{
    QLOG_TRACE() << "EndpointManager::receiveCharacter()";
    CharacterPayload payload;
    const QByteArray bytes = reply->readAll();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(payload) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing character payload:" << parseContext.makeErrorString();
        payload.character.reset();
    };
    if (payload.character) {
        emit characterReceived(payload.character);
    };
}

void EndpointManager::receiveStashList(QNetworkReply* reply)
{
    QLOG_TRACE() << "EndpointManager::receiveStashList()";
    StashListPayload payload;
    const QByteArray bytes = reply->readAll();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(payload) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing stash list payload:" << parseContext.makeErrorString();
        payload.stashes = {};
    };
    emit stashListReceived(payload.stashes);
}

void EndpointManager::receiveStash(QNetworkReply* reply)
{
    QLOG_TRACE() << "EndpointManager::receiveStash()";
    StashPayload payload;
    const QByteArray bytes = reply->readAll();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(payload) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing stash payload:" << parseContext.makeErrorString();
        payload.stash.reset();
    };
    if (payload.stash) {
        emit stashReceived(payload.stash);
    };
}
