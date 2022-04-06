#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>

#include <wobjectimpl.h>

#include "access.hpp"
#include <Items/advisor_item.hpp>

namespace Service
{
W_OBJECT_IMPL(access)

access::access(const QString& url,
               const QString &authentication_arguments,
               const QString &extra_arguments)
    : prefix{url + '/'}
    , auth_args{authentication_arguments}
    , suffix{extra_arguments}
    , rqst{}
    , user{}
{
    auto conf = QSslConfiguration::defaultConfiguration();
    rqst.setSslConfiguration(conf);
    rqst.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    connect(this, &QNetworkAccessManager::sslErrors,
            this, [](QNetworkReply* reply,
            const QList<QSslError>& errors)
    { reply->ignoreSslErrors(errors); });
}

void access::authenticate(const QString& username,
                          const QString& password)
{
    QUrl url{prefix + auth_args
                + '?' + "userName=" + username
                + '&' + "password=" + password
                + '&' + suffix
                + "&rememberMe=True"};

    rqst.setUrl(url);

    authenticating = true;
    QNetworkReply* reply = get(rqst);
    //     just for working
    //    emit loggedIn(true);

    connect(reply, &QNetworkReply::finished,
            [=]()
    {
        if (reply->error())
        {
            if (authenticating)
            {
                authenticating = false;
                emit loggedIn(false);
            }

            qDebug() << reply->errorString();
        }
        else
        {
            const auto res = reply->readAll();
            const auto json = QJsonDocument::fromJson(res).object();

            if (json.contains("sessionId"))
            {
                if (authenticating)
                {
                    delete user;
                    user = new Data::People::advisor_item();
                    authenticating = false;
                    sessionId = json["sessionId"].toString();
                    const auto displayName = json["displayName"].toString();
                    auto lastAndFirst = displayName.split(" ");
                    user->firstName = lastAndFirst[1];
                    user->lastName = lastAndFirst[0];

                    emit loggedIn(true);
                }
            }
        }

        reply->deleteLater();
    });
}

void access::getFromKey(const char* key,
                        const std::function<void(const QByteArray&)>& callback)
{
    setRequest(key);
    QNetworkReply* reply = get(rqst);
    setCallback(reply, callback);
}

void access::putToKey(const char* key,
                      const QByteArray &data,
                      const std::function<void (const QByteArray &)> &callback)
{
    setRequest(key);
    QNetworkReply* reply = put(rqst, data);
    setCallback(reply, callback);
}

void access::postToKey(const char* key,
                       const QByteArray &data,
                       const std::function<void (const QByteArray &)> &callback)
{
    setRequest(key);
    QNetworkReply* reply = post(rqst, data);
    setCallback(reply, callback);
}

void access::setCallback(QNetworkReply* reply,
                         const std::function<void (const QByteArray &)> &callback)
{
    connect(reply, &QNetworkReply::finished,
            [=]()
    {
        callback(reply->readAll());
        reply->deleteLater();
    });
}

void access::setRequest(const char* key)
{
    QUrl url{prefix + key + '?'
                + "sessionId=" + sessionId
                + '&' + suffix};

    rqst.setUrl(url);
}

}
