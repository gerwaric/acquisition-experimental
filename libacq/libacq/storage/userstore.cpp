#include <libacq/storage/userstore.h>

#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>

UserStore::UserStore(const QString& directory, QObject* parent)
    : QObject(parent)
    , m_data_directory(directory) {}

void UserStore::setUsername(const QString& username)
{
    if (m_username == username) {
        return;
    };

    if (m_db.isOpen()) {
        m_db.close();
    };

    m_username = username;

    const QString filename = m_data_directory
        + QDir::separator() + "data"
        + QDir::separator() + m_username
        + QDir::separator() + "user_data.sqlite3";

    m_db = QSqlDatabase::addDatabase("QSQLITE", filename);
    m_db.setDatabaseName(filename);
    if (m_db.open() == false) {
        QLOG_ERROR() << "Failed to open QSQLITE database:" << filename << ":" << m_db.lastError().text();
        return;
    };

    QSqlQuery query(m_db);
    query.prepare("CREATE TABLE IF NOT EXISTS data (key TEXT PRIMARY KEY, value TEXT)");
    if (query.exec() == false) {
        QLOG_ERROR() << "League store failed to create character table:" << query.lastError().text();
    };
};

void UserStore::setInt(const QString& name, int value)
{
    setValue(name, value);
}

int UserStore::getInt(const QString& name)
{
    return getValue(name).toInt();
}

void UserStore::setBool(const QString& name, bool value)
{
    setValue(name, value);
}

bool UserStore::getBool(const QString& name)
{
    return getValue(name).toBool();
}

void UserStore::setString(const QString& name, const QString& value)
{
    setValue(name, value);
}

QString UserStore::getString(const QString& name)
{
    return getValue(name).toString();
}

void UserStore::setDateTime(const QString& name, const QDateTime& value)
{
    setValue(name, value.toString());
}

QDateTime UserStore::getDateTime(const QString& name)
{
    return QDateTime::fromString(getValue(name).toString());
}

void UserStore::setValue(const QString& name, const QVariant& value)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT OR REPLACE INTO data (key, value) VALUES (?, ?)");
    query.bindValue(0, name);
    query.bindValue(1, value);
    if (!query.exec()) {
        QLOG_ERROR() << "Error writing" << name << "to the user database:" << query.lastError().text();
    };
}

QVariant UserStore::getValue(const QString& name)
{
    QSqlQuery query(m_db);
    query.prepare("SELECT value FROM data WHERE key = ?");
    query.bindValue(0, name);
    if (!query.exec()) {
        QLOG_ERROR() << "Error selecting" << name << "from user database:" << query.lastError().text();
        return QVariant();
    };
    if (!query.first()) {
        QLOG_ERROR() << "Error reading" << name << "from user database:" << query.lastError().text();
        return QVariant();
    };
    return query.value(0);
}
