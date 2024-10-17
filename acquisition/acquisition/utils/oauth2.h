#pragma once

#include <QtNetworkAuth/qoauthglobal.h>
#include <QtNetworkAuth/qabstractoauth2.h>

//QT_BEGIN_NAMESPACE

class QUrl;
class QString;
class QNetworkAccessManager;

class QOAuth2AuthorizationCodeFlowPrivate;
class Q_OAUTH_EXPORT MyOAuth2AuthorizationCodeFlow : public QAbstractOAuth2
{
    Q_OBJECT
        Q_PROPERTY(QUrl accessTokenUrl
            READ accessTokenUrl
            WRITE setAccessTokenUrl
            NOTIFY accessTokenUrlChanged)
        Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")

public:
    explicit MyOAuth2AuthorizationCodeFlow(QObject* parent = nullptr);
    explicit MyOAuth2AuthorizationCodeFlow(QNetworkAccessManager* manager,
        QObject* parent = nullptr);

    MyOAuth2AuthorizationCodeFlow(const QString& clientIdentifier,
        QNetworkAccessManager* manager,
        QObject* parent = nullptr);

    MyOAuth2AuthorizationCodeFlow(const QUrl& authorizationUrl,
        const QUrl& accessTokenUrl,
        QNetworkAccessManager* manager,
        QObject* parent = nullptr);

    MyOAuth2AuthorizationCodeFlow(const QString& clientIdentifier,
        const QUrl& authorizationUrl,
        const QUrl& accessTokenUrl,
        QNetworkAccessManager* manager,
        QObject* parent = nullptr);

    ~MyOAuth2AuthorizationCodeFlow();

    QUrl accessTokenUrl() const;
    void setAccessTokenUrl(const QUrl& accessTokenUrl);

    enum class PkceMethod : quint8 {
        S256,
        Plain,
        None = 255,
    };
    Q_ENUM(PkceMethod)

        void setPkceMethod(PkceMethod method, qsizetype length = 43);
    PkceMethod pkceMethod() const noexcept;

public Q_SLOTS:
    void grant() override;
    void refreshAccessToken();

protected:
    QUrl buildAuthenticateUrl(const QMultiMap<QString, QVariant>& parameters = {});
    void requestAccessToken(const QString& code);
    void resourceOwnerAuthorization(const QUrl& url,
        const QMultiMap<QString, QVariant>& parameters = {}) override;

Q_SIGNALS:
    void accessTokenUrlChanged(const QUrl& accessTokenUrl);

private:
    Q_DISABLE_COPY(MyOAuth2AuthorizationCodeFlow)
    //Q_DECLARE_PRIVATE(MyOAuth2AuthorizationCodeFlow)
};

//QT_END_NAMESPACE

//#endif // QT_NO_HTTP

//#endif // QOAUTH2AUTHORIZATIONCODEFLOW_H
