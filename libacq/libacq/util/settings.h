 #pragma once

#include <QsLog/QsLog.h>

#include <QObject>

class QSettings;

class Settings : public QObject {
    Q_OBJECT
public:
    Settings(const QString& directory, QObject* parent);

    QString filename() const { return m_filename; };
    QString username() const;
    QString league() const;
    QString sessionId() const;
    QsLogging::Level loggingLevel() const;

signals:
    void usernameChanged(const QString& username);
    void leagueChanged(const QString& league);
    void sessionIdChanged(const QString& session_id);
    void loggingLevelChanged(QsLogging::Level level);

public slots:
    void setUsername(const QString& username);
    void setLeague(const QString& league);
    void setSessionId(const QString& session_id);
    void setLoggingLevel(QsLogging::Level level);

private:
    static QString makeFilename(const QString& directory);

    const QString m_filename;
    QSettings* m_settings;
};
