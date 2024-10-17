/*
    Acquisition is a stash management program for Path of Exile

    Copyright(C) 2024 Gerwaric

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

//#include <main.h>

#include <acquisition/acquisition.h>
#include <acquisition/constants.h>
#include <acquisition/data_stores/league_data_store.h>
#include <acquisition/data_model/tree_model.h>
#include <acquisition/utils/utils.h>
#include <acquisition/api_types/character.h>
#include <acquisition/api_types/stash_tab.h>

#include <QsLog/QsLog.h>

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStandardPaths>

#include <QByteArray>
#include <QString>
#include <QDesktopServices>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthUriSchemeReplyHandler>
#include <QOAuthHttpServerReplyHandler>
#include <QCryptographicHash>
#include <QUuid>
#include <QUrl>
#include <QAbstractOAuth>
#include <QUrlQuery>
#include <QMultiMap>

#ifdef _DEBUG
constexpr QsLogging::Level DefaultLogging = QsLogging::DebugLevel;
#else
constexpr QsLogging::Level DefaultLogging = QsLogging::InfoLevel;
#endif

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>
#include <QQmlEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QCommandLineOption data_directory_option(
        { "d", "data-directory" },
        "Location for data files",
        "data_directory",
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));

    QCommandLineOption logging_level_option(
        { "l", "logging-level" },
        "off, fatal, error, warn, info, debug, trace",
        "logging_level",
        utils::logLevelName(DefaultLogging));

    QCommandLineParser p;
    p.setApplicationDescription("Inventory and forum shop management for Path of Exile");
    p.addHelpOption();
    p.addVersionOption();
    p.addOption(data_directory_option);
    p.addOption(logging_level_option);
    p.process(app);

    const QsLogging::Level logging_level = utils::logLevel(p.value(logging_level_option));
    const QString data_directory = p.value(data_directory_option);
    const QString log_filename = Application::makeLogFilename(data_directory);

    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(logging_level);
    logger.addDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(QsLogging::DestinationFactory::MakeFileDestination(log_filename,
        QsLogging::EnableLogRotation,
        QsLogging::MaxSizeBytes(10 * 1024 * 1024),
        QsLogging::MaxOldLogCount(0)));

    const QString banner_text("- Starting " APP_NAME " version " APP_VERSION_STRING " -");
    const QString banner_line(banner_text.length(), '-');

    QLOG_INFO() << banner_line;
    QLOG_INFO() << banner_text;
    QLOG_INFO() << banner_line;

    QLOG_DEBUG() << "Creating application";
    Application acquisition(data_directory);

    QLOG_DEBUG() << "Creating QML engine";
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [](const QUrl& url) {
            QLOG_FATAL() << "QML error loading" << url.toString();
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    QLOG_DEBUG() << "Setting root context";
    engine.rootContext()->setContextProperty("Acquisition", &acquisition);

    QLOG_DEBUG() << "Loading QML module";
    engine.loadFromModule("MyAcquisition", "Main");

    QLOG_DEBUG() << "Running application";
    return app.exec();

    /*
    QLOG_INFO() << "setting up oauth";

    QOAuth2AuthorizationCodeFlow m_oauth;
    m_oauth.setUserAgent(USER_AGENT);
    m_oauth.setAuthorizationUrl(QUrl("https://www.pathofexile.com/oauth/authorize"));
    m_oauth.setAccessTokenUrl(QUrl("https://www.pathofexile.com/oauth/token"));
    m_oauth.setClientIdentifier("acquisition");
    m_oauth.setScope("account:leagues account:stashes account:characters");
    m_oauth.setPkceMethod(QOAuth2AuthorizationCodeFlow::PkceMethod::S256);

    QOAuthHttpServerReplyHandler m_handler(0, qApp);
    m_handler.setCallbackPath("/auth/path-of-exile");
    m_handler.setCallbackText("Callback text");
    m_oauth.setReplyHandler(&m_handler);
    m_oauth.setModifyParametersFunction(
        [&](QAbstractOAuth::Stage stage, QMultiMap<QString, QVariant>* parameters) {
            if (parameters->contains("redirect_uri")) {
                QUrl url("http://127.0.0.1");
                url.setPort(m_handler.port());
                url.setPath(m_handler.callbackPath(), QUrl::ParsingMode::StrictMode);
                parameters->replace("redirect_uri", url.toString().toLatin1());
            };
            for (const auto& key : parameters->keys()) {
                QLOG_INFO() << "****" << int(stage) << ":" << key << "=" << parameters->value(key);
            };
        });

    QObject::connect(&m_handler, &QOAuthHttpServerReplyHandler::callbackDataReceived, qApp, [=](const QByteArray& data) {
        QLOG_INFO() << "callback received:" << data;
    });

    QObject::connect(&m_handler, &QOAuthHttpServerReplyHandler::replyDataReceived, qApp, [=](const QByteArray& data) {
        QLOG_INFO() << "reply data:" << data;
    });

    QObject::connect(&m_oauth, &QAbstractOAuth::authorizeWithBrowser, qApp, &QDesktopServices::openUrl);
    QObject::connect(&m_oauth, &QAbstractOAuth::granted, qApp, [&]() {
        // Here we use QNetworkRequestFactory to store the access token
        QLOG_INFO() << "Bearer token" << m_oauth.token().toLatin1();
        m_handler.close();
    });
    QObject::connect(&m_handler, &QOAuthHttpServerReplyHandler::tokensReceived, qApp,
        [&](const QVariantMap& tokens) {
                         for (const auto& item : tokens.keys()) {
                             QLOG_INFO() << "TOKENS" << item << tokens.value(item).toString();
                         };
        });

    QLOG_INFO() << "calling listen";

    // Initiate the authorization
    if (m_handler.listen()) {
        QLOG_INFO() << "calling grant";
        m_oauth.grant();
    };
    m_oauth.grant();
    */

}
