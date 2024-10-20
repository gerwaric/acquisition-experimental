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

#include <acquisition.h>
#include <acquisition/command_line.h>

#include <QsLog/QsLog.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    // Process the command line options.
    CommandLine command_line(app);
    const QsLogging::Level logging_level = command_line.logging_level();
    const QString data_directory = command_line.data_directory();

    // Setup logging before creating the QML engine so that we can configure
    // use the data directory for log messages now. Otherwise we'd have to wait
    // until after the Acquisition singleton instance is constructed to set
    // the data directory. This would leave us unable to log anything during
    // the construction of that object.
    const QString logging_filename = Acquisition::makeLogFilename(data_directory);
    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(logging_level);
    logger.addDestination(QsLogging::DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(QsLogging::DestinationFactory::MakeFileDestination(logging_filename,
        QsLogging::EnableLogRotation,
        QsLogging::MaxSizeBytes(10 * 1024 * 1024),
        QsLogging::MaxOldLogCount(0)));

    // Create the QML application engine, which will create its own instance
    // of the Acquisition object for us to use.
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [](const QUrl& url) {
            QLOG_FATAL() << "QML object creation failed:" << url.toString();
            QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    // Get the Acquisition object so we can set the data directory.
    Acquisition* acquisition = engine.singletonInstance<Acquisition*>("MyAcquisition", "Acquisition");
    if (!acquisition) {
        QLOG_FATAL() << "Unable to retrieve the Acquisition instance";
        exit(EXIT_FAILURE);
    };

    // Set the data directory before loading the engine module so that
    // Acquisition can properly setup all the stuff needed by QML.
    acquisition->init(data_directory);

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
