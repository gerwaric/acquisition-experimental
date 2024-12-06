#include "settings.h"

#include <libacq/utils/utils.h>

#include <QsLog/QsLog.h>

#include <QDir>
#include <QSettings>

namespace {
    constexpr const char* LOGGING_LEVEL = "logging_level";
    constexpr const char* USERNAME = "username";
    constexpr const char* LEAGUE = "league";
    constexpr const char* SESSION_ID = "session_id";
}

Settings::Settings(const QString& directory, QObject* parent)
    : QObject(parent)
    , m_filename(makeFilename(directory))
{
    m_settings = new QSettings(m_filename, QSettings::IniFormat, this);

    auto& logger = QsLogging::Logger::instance();
    const QsLogging::Level active_level = logger.loggingLevel();
    const QsLogging::Level saved_level = loggingLevel();
    if (active_level != saved_level) {
        QLOG_INFO() << "Settings: changing initial logging level from" << active_level << "to" << saved_level;
        logger.setLoggingLevel(saved_level);
    };
}

QString Settings::makeFilename(const QString& directory)
{
    return directory + QDir::separator() + "settings-new.ini";
}

QString Settings::username() const
{
    return m_settings->value(USERNAME).toString();
}

QString Settings::league() const
{
    return m_settings->value(LEAGUE).toString();
}

QString Settings::sessionId() const
{
    return m_settings->value(SESSION_ID).toString();
}

QsLogging::Level Settings::loggingLevel() const
{
    return utils::loggingLevel(m_settings->value(LOGGING_LEVEL).toString());
}

void Settings::setUsername(const QString& username)
{
    const QString previous_value = m_settings->value(USERNAME).toString();
    if (previous_value != username) {
        QLOG_INFO() << "Changing username to" << username;
        m_settings->setValue(USERNAME, username);
        emit usernameChanged(username);
    };
}

void Settings::setLeague(const QString& league)
{
    const QString previous_value = m_settings->value(LEAGUE).toString();
    if (previous_value != league) {
        QLOG_INFO() << "Changing league to" << league;
        m_settings->setValue(LEAGUE, league);
        emit leagueChanged(league);
    };
}

void Settings::setSessionId(const QString& session_id)
{
    const QString previous_value = m_settings->value(SESSION_ID).toString();
    if (previous_value != session_id) {
        QLOG_INFO() << "Changing session id";
        m_settings->setValue(SESSION_ID, session_id);
        emit sessionIdChanged(session_id);
    };
}

void Settings::setLoggingLevel(QsLogging::Level level)
{
    const QString name = utils::loggingLevelName(level);
    const QString current_name = m_settings->value(LOGGING_LEVEL).toString();
    const QsLogging::Level current_level = utils::loggingLevel(current_name);
    const QsLogging::Level active_level = QsLogging::Logger::instance().loggingLevel();
    if (current_level != active_level) {
        QLOG_WARN() << "Settings: active logging level does not match current setting";
    };
    if (level != current_level) {
        m_settings->setValue(LOGGING_LEVEL, name);
        if (level > QsLogging::InfoLevel) {
            QLOG_INFO() << "Changing log level from" << current_name << "to" << name;
        };
        QsLogging::Logger::instance().setLoggingLevel(level);
        if (active_level > QsLogging::InfoLevel) {
            QLOG_INFO() << "Changed log level from" << current_name << "to" << name;
        };
        emit loggingLevelChanged(level);
    };
}
