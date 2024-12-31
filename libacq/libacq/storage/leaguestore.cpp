#include <libacq/storage/leaguestore.h>

#include <QsLog/QsLog.h>

#include <QCryptographicHash>
#include <QDateTime>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

LeagueStore::LeagueStore(const QString& directory, QObject* parent)
    : QObject(parent)
    , m_data_directory(directory) {}

void LeagueStore::setUsername(const QString& username)
{
    if (m_username == username) {
        return;
    };
    m_username = username;
    if (m_db.isOpen()) {
        m_db.close();
        setLeague(m_league);
    };
}

void LeagueStore::setLeague(const QString& league)
{
    if (m_league == league) {
        if (m_db.isOpen()) {
            return;
        };
    };

    if (m_db.isOpen()) {
        m_db.close();
    };

    m_league = league;

    const QString filename = m_data_directory
         + QDir::separator() + "data"
         + QDir::separator() + m_username
         + QDir::separator() + "league_data"
         + QDir::separator() + m_league + ".sqlite3";
    m_db = QSqlDatabase::addDatabase("QSQLITE", filename);
    m_db.setDatabaseName(filename);
    if (m_db.open() == false) {
        QLOG_ERROR() << "Failed to open QSQLITE database:" << filename << ":" << m_db.lastError().text();
        return;
    };

    QSqlQuery query(m_db);

    query.prepare("CREATE TABLE IF NOT EXISTS metadata ("
        "name TEXT PRIMARY KEY, "
        "value TEXT)");

    if (query.exec() == false) {
        QLOG_ERROR() << "League store failed to create data table:" << query.lastError().text();
    };

    query.prepare("CREATE TABLE IF NOT EXISTS characters ("
        "id TEXT PRIMARY KEY, "
        "name TEXT, "
        "json TEXT, "
        "timestamp TEXT, "
        "hash TEXT)");
    
    if (query.exec() == false) {
        QLOG_ERROR() << "League store failed to create character table:" << query.lastError().text();
    };
    
    query.prepare("CREATE TABLE IF NOT EXISTS stash_tabs ("
        "id TEXT PRIMARY KEY, "
        "name TEXT, "
        "type TEXT, "
        "parent TEXT, "
        "json TEXT, "
        "timestamp TEXT, "
        "hash TEXT)");

    if (query.exec() == false) {
        QLOG_ERROR() << "League store failed to create stash_tabs table:" << query.lastError().text();
    };

    query.prepare("CREATE TABLE IF NOT EXISTS buyouts ("
        "id TEXT PRIMARY KEY, "
        "last_update TEXT, "
        "data TEXT)");
    
    if (query.exec() == false) {
        QLOG_ERROR() << "League store failed to create buyout table:" << query.lastError().text();
    };
}

QStringList LeagueStore::getCharacterList()
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot get character list: the database is not open";
        return {};
    };

    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM characters");

    if (!query.exec()) {
        QLOG_ERROR() << "Error selecting characters:" << query.lastError().text();
        return {};
    };

    QStringList character_ids;
    int i = 0;
    while (query.next()) {
        ++i;
        if (query.lastError().isValid()) {
            QLOG_ERROR() << "Error getting character_id" << i << ":" << query.lastError().text();
            break;
        };
        character_ids.push_back(query.value(0).toString());
    };
    character_ids.sort();
    return character_ids;
}

QStringList LeagueStore::getStashList()
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot get stash list: the database is not open";
        return {};
    };

    QSqlQuery query(m_db);
    query.prepare("SELECT id FROM stash_tabs");

    if (!query.exec()) {
        QLOG_ERROR() << "Error selecting characters:" << query.lastError().text();
        return {};
    };

    QStringList stash_ids;
    int i = 0;
    while (query.next()) {
        ++i;
        if (query.lastError().isValid()) {
            QLOG_ERROR() << "Error getting stash_id" << i << ":" << query.lastError().text();
            break;
        };
        stash_ids.push_back(query.value(0).toString());
    };
    return stash_ids;
}

std::unique_ptr<poe_api::Character> LeagueStore::getCharacter(const QString& id)
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot get character: the database is not open";
        return {};
    };

    QSqlQuery query(m_db);
    query.prepare("SELECT json FROM characters WHERE id = ?");
    query.bindValue(0, id);

    if (!query.exec()) {
        QLOG_ERROR() << "Error selecting character with id" << id << ":" << query.lastError().text();
        return nullptr;
    };
    if (!query.first()) {
        QLOG_ERROR() << "Error getting character with id" << id << ":" << query.lastError().text();
        return nullptr;
    };

    auto character = std::make_unique<poe_api::Character>();
    const std::string bytes = query.value(0).toString().toStdString(); //query.value(0).toString().toStdString();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(character) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing character:" << parseContext.makeErrorString();
    };
    return std::move(character);
}

std::unique_ptr<poe_api::StashTab> LeagueStore::getStash(const QString& id)
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot get stash: the database is not open";
        return {};
    };

    QSqlQuery query(m_db);
    query.prepare("SELECT json FROM stash_tabs WHERE id = ?");
    query.bindValue(0, id);

    if (!query.exec()) {
        QLOG_ERROR() << "Error selecting stash tab with id" << id << ":" << query.lastError().text();
        return nullptr;
    };
    if (!query.first()) {
        QLOG_ERROR() << "Error getting stash tab with id" << id << ":" << query.lastError().text();
        return nullptr;
    };

    auto stash_tab = std::make_unique<poe_api::StashTab>();
    const std::string bytes = query.value(0).toString().toStdString();
    JS::ParseContext parseContext(bytes);
    if (parseContext.parseTo(stash_tab) != JS::Error::NoError) {
        QLOG_ERROR() << "Error parsing character:" << parseContext.makeErrorString();
    };
    return std::move(stash_tab);
}

poe_api::CharacterList LeagueStore::getCharacters()
{
    const QStringList character_ids = getCharacterList();
    poe_api::CharacterList characters;
    characters.reserve(character_ids.size());
    for (const auto& id : character_ids) {
        auto character = getCharacter(id);
        if (!character) {
            QLOG_ERROR() << "League data store returned an invalid character:" << id;
            continue;
        };
        characters.push_back(std::move(character));
    };
    return characters;
}

poe_api::StashTabList LeagueStore::getStashes()
{
    const QStringList stash_ids = getStashList();
    poe_api::StashTabList stashes;
    stashes.reserve(stash_ids.size());
    for (const auto& id : stash_ids) {
        auto stash = getStash(id);
        if (!stash) {
            QLOG_ERROR() << "League data store returned an invalid stash:" << id;
            continue;
        };
        stashes.push_back(std::move(stash));
    };

    // Sort based on index.
    std::sort(stashes.begin(), stashes.end(),
        [](const std::unique_ptr<poe_api::StashTab>& a, const std::unique_ptr<poe_api::StashTab>& b) {
            return a->index.value_or(0) < b->index.value_or(0);
        });

    return stashes;
}

void LeagueStore::storeCharacter(const poe_api::Character& character)
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot store character: the database is not open";
        return;
    };

    const std::string value = JS::serializeStruct(character, JS::SerializerOptions::Compact);
    const QByteArray json = QByteArray(value.data(), value.size());
    const QString hash = generateHash(json);
    const QString timestamp = QDateTime::currentDateTime().toLocalTime().toString();

    QLOG_DEBUG() << "Character:" << json;

    QSqlQuery query(m_db);
    query.prepare("INSERT OR REPLACE INTO characters (id, name, json, timestamp, hash)"
        "VALUES (:id, :name, :json, :timestamp, :hash)");
    query.bindValue(":id", character.id);
    query.bindValue(":name", character.name);
    query.bindValue(":json", json);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":hash", hash);

    if (query.exec() == false) {
        QLOG_ERROR() << "Error storing character" << character.name << ":" << query.lastError().text();
    };
}

void LeagueStore::storeStash(const poe_api::StashTab& stash_tab)
{
    if (!m_db.isOpen()) {
        QLOG_ERROR() << "Cannot store stash tab: the database is not open";
        return;
    };

    const std::string value = JS::serializeStruct(stash_tab, JS::SerializerOptions::Compact);
    const QByteArray json(value.data(), value.size());
    const QString hash = generateHash(json);
    const QString timestamp = QDateTime::currentDateTime().toLocalTime().toString();

    QSqlQuery query(m_db);
    query.prepare("INSERT OR REPLACE INTO stash_tabs (id, name, type, parent, json, timestamp, hash) "
        "VALUES (:id, :name, :type, :parent, :json, :timestamp, :hash)");
    query.bindValue(":id", stash_tab.id);
    query.bindValue(":name", stash_tab.name);
    query.bindValue(":type", stash_tab.type);
    query.bindValue(":parent", stash_tab.parent.value_or(""));
    query.bindValue(":json", json);
    query.bindValue(":timestamp", timestamp);
    query.bindValue(":hash", hash);

    if (query.exec() == false) {
        QLOG_ERROR() << "Error storing stash tab" << stash_tab.name << ":" << query.lastError().text();
    };
}

QString LeagueStore::generateHash(const QString& data)
{
    const QCryptographicHash::Algorithm algorithm = QCryptographicHash::Blake2b_256;
    const QByteArray hash = QCryptographicHash::hash(data.toUtf8(), algorithm);
    return QString(hash.toHex());
}
