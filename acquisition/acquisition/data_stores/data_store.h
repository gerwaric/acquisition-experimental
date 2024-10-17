#pragma once

#include <QObject>

#include <QSqlDatabase>

class DataStore : public QObject {
    Q_OBJECT
public:

protected:
    void connect(const QString& filename);
    void simpleQuery(const QString& query);
    QString stringQuery(const QString& query);
    QStringList stringListQuery(const QString& query);

private:
    QString m_filename;
    QSqlDatabase m_database;
};