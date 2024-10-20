#pragma once

#include <QsLog/QsLogLevel.h>

#include <QString>

class QCoreApplication;

#ifdef _DEBUG
constexpr QsLogging::Level DEFAULT_LOGGING_LEVEL = QsLogging::DebugLevel;
#else
constexpr QsLogging::Level DefaultLogging = QsLogging::InfoLevel;
#endif

class CommandLine {
public:
    CommandLine(const QCoreApplication& app);

    QsLogging::Level logging_level() const { return m_logging_level; };
    const QString& data_directory() const { return m_data_directory; };

private:
    QsLogging::Level m_logging_level{DEFAULT_LOGGING_LEVEL};
    QString m_data_directory;
};
