#include <acquisition/settings.h>

#include <acquisition/utils/utils.h>

#include <QsLog/QsLog.h>

#include <QDir>
#include <QSettings>

Settings::Settings(QObject* parent, const QString& directory)
    : QObject(parent)
    , m_filename(makeFilename(directory))
{
    m_settings = new QSettings(m_filename, QSettings::IniFormat, this);
}

QString Settings::makeFilename(const QString& directory)
{
    return directory + QDir::separator() + "settings-new.ini";
}

void Settings::sendSignals()
{
    const QString log_level_name = m_settings->value("log_level").toString();
    const auto current_level = QsLogging::Logger::instance().loggingLevel();
    if (log_level_name.isEmpty()) {
        // Settings did not contain log_level, so use the current value.
        m_settings->setValue("log_level", utils::logLevelName(current_level));
    } else {
        // Settings contained log_level, so use this value.
        const auto settings_level = utils::logLevel(log_level_name);
        if (current_level != settings_level) {
            QsLogging::Logger::instance().setLoggingLevel(settings_level);
            emit logLevelChanged(settings_level);
        };
    };

    if (!username().isEmpty()) {
        emit usernameChanged(username());
    };
    if (!league().isEmpty()) {
        emit leagueChanged(league());
    };
    if (!sessionId().isEmpty()) {
        emit sessionIdChanged(sessionId());
    };
}

QString Settings::username() const
{
    return m_settings->value("username").toString();
}

QString Settings::league() const
{
    return m_settings->value("league").toString();
}

QString Settings::sessionId() const
{
    return m_settings->value("session_id").toString();
}

QsLogging::Level Settings::logLevel() const
{
    const QString name = m_settings->value("log_level").toString();
    return utils::logLevel(name);
}

void Settings::setUsername(const QString& username)
{
    const QString previous_value = m_settings->value("username").toString();
    if (previous_value != username) {
        QLOG_INFO() << "Changing username to" << username;
        m_settings->setValue("username", username);
        emit usernameChanged(username);
    };
}

void Settings::setLeague(const QString& league)
{
    const QString previous_value = m_settings->value("league").toString();
    if (previous_value != league) {
        QLOG_INFO() << "Changing league to" << league;
        m_settings->setValue("league", league);
        emit leagueChanged(league);
    };
}

void Settings::setSessionId(const QString& session_id)
{
    const QString previous_value = m_settings->value("session_id").toString();
    if (previous_value != session_id) {
        QLOG_INFO() << "Changing session id";
        m_settings->setValue("session_id", session_id);
        emit sessionIdChanged(session_id);
    };
}

void Settings::setLogLevel(QsLogging::Level level)
{
    const QString previous_value = m_settings->value("logging_level").toString();
    const QString next_value = utils::logLevelName(level);
    if (0 != previous_value.compare(next_value, Qt::CaseInsensitive)) {
        QLOG_INFO() << "Changing log level to" << next_value;
        m_settings->setValue("log_level", next_value);
        QsLogging::Logger::instance().setLoggingLevel(level);
        emit logLevelChanged(level);
    };
}
