#include <libacq/util/commandline.h>

#include <libacq/util/utils.h>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QStandardPaths>

CommandLine::CommandLine(const QCoreApplication& app)
{
    QCommandLineOption data_directory_option(
        { "d", "data-directory" },
        "Location for settings and data files",
        "data_directory",
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));

    QCommandLineOption logging_level_option(
        { "l", "logging-level" },
        "Logging options: 'off', 'fatal', 'error', 'warn', 'info', 'debug', trace",
        "logging_level");

    QCommandLineParser p;
    p.setApplicationDescription("Inventory and forum shop management for Path of Exile");
    p.addHelpOption();
    p.addVersionOption();
    p.addOption(data_directory_option);
    p.addOption(logging_level_option);
    p.process(app);

    if (p.isSet(logging_level_option)) {
        m_logging_level = utils::loggingLevel(p.value(logging_level_option));
    };

    m_data_directory = p.value(data_directory_option);

    QLOG_DEBUG() << "Command Line: data directory is" << m_data_directory;
    QLOG_DEBUG() << "Command Line: logging level is" << utils::loggingLevelName(m_logging_level);
}
