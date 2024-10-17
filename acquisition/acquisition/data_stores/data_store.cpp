#include <acquisition/data_stores/data_store.h>

#include <QsLog/QsLog.h>

#include <QSqlQuery>

void DataStore::simpleQuery(const QString& query)
{
    QSqlQuery sql_query(query, m_database);
    if (sql_query.exec() == false) {
        QLOG_ERROR() << "Sql query failed:" << query << ":" << sql_query.lastError().text();
    };
}

QString DataStore::stringQuery(const QString& query)
{
    QSqlQuery sql_query(m_database);
    sql_query.prepare("SELECT data FROM characters WHERE id = ?");
    sql_query.bindValue(0, id);
    if (!sql_query.exec()) {
        QLOG_ERROR() << "Error selecting character with id" << id << ":" << query.lastError().text();
        return nullptr;
    };
    if (!sql_query.first()) {
        QLOG_ERROR() << "Error getting character with id" << id << ":" << query.lastError().text();
        return nullptr;
    };

}