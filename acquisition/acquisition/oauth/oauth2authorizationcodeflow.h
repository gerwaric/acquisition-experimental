// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef OAUTH2AUTHORIZATIONCODEFLOW_H
#define OAUTH2AUTHORIZATIONCODEFLOW_H

#ifndef QT_NO_HTTP

#include <QtNetworkAuth/qoauthglobal.h>
#include <QtNetworkAuth/qabstractoauth2.h>

QT_BEGIN_NAMESPACE

class QUrl;
class QString;
class QNetworkAccessManager;

class OAuth2AuthorizationCodeFlowPrivate;
class Q_OAUTH_EXPORT OAuth2AuthorizationCodeFlow : public QAbstractOAuth2
{
    Q_OBJECT
    Q_PROPERTY(QUrl accessTokenUrl
               READ accessTokenUrl
               WRITE setAccessTokenUrl
               NOTIFY accessTokenUrlChanged)

public:
    explicit OAuth2AuthorizationCodeFlow(QObject *parent = nullptr);
    explicit OAuth2AuthorizationCodeFlow(QNetworkAccessManager *manager,
                                          QObject *parent = nullptr);

    OAuth2AuthorizationCodeFlow(const QString &clientIdentifier,
                                 QNetworkAccessManager *manager,
                                 QObject *parent = nullptr);

    OAuth2AuthorizationCodeFlow(const QUrl &authorizationUrl,
                                 const QUrl &accessTokenUrl,
                                 QNetworkAccessManager *manager,
                                 QObject *parent = nullptr);

    OAuth2AuthorizationCodeFlow(const QString &clientIdentifier,
                                 const QUrl &authorizationUrl,
                                 const QUrl &accessTokenUrl,
                                 QNetworkAccessManager *manager,
                                 QObject *parent = nullptr);

    ~OAuth2AuthorizationCodeFlow();

    QUrl accessTokenUrl() const;
    void setAccessTokenUrl(const QUrl &accessTokenUrl);

public Q_SLOTS:
    void grant() override;
    void refreshAccessToken();

protected:
    QUrl buildAuthenticateUrl(const QMultiMap<QString, QVariant> &parameters = {});
    void requestAccessToken(const QString &code);
    void resourceOwnerAuthorization(const QUrl &url,
                                    const QMultiMap<QString, QVariant> &parameters = {}) override;

Q_SIGNALS:
    void accessTokenUrlChanged(const QUrl &accessTokenUrl);

private:
    //GERWARIC Q_DISABLE_COPY(QAuth2AuthorizationCodeFlow)
    //GERWARIC Q_DECLARE_PRIVATE(OAuth2AuthorizationCodeFlow)
};

QT_END_NAMESPACE

#endif // QT_NO_HTTP

#endif // QOAUTH2AUTHORIZATIONCODEFLOW_H
