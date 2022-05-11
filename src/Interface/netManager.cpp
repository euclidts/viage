#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

#include <wobjectimpl.h>

#include "netManager.hpp"
#include <Items/user_item.hpp>

namespace Interface
{
W_OBJECT_IMPL(netManager)

netManager::netManager(const QString& url,
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

void netManager::authenticate(const QString& username,
                              const QString& password)
{
    QUrl url{prefix + auth_args
                + '?' + "userName=" + username
                + '&' + "password=" + password
                + '&' + suffix
                + "&rememberMe=True"};

    rqst.setUrl(url);

    authenticating = true;
    auto* reply = get(rqst);

    connect(reply, &QNetworkReply::finished,
            [this, reply]()
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
                    user = new Data::People::user_item();
                    authenticating = false;

                    if (json.contains("sessionId") && json["sessionId"].isString())
                    {
                        const auto str{json["sessionId"].toString()};
                        rqst.setRawHeader("sessionId",
                                          QByteArray::fromStdString(str.toStdString()));
                    }

                    if (json.contains("displayName") && json["displayName"].isString())
                    {
                        const auto displayName = json["displayName"].toString();
                        auto lastAndFirst = displayName.split(" ");
                        user->firstName = lastAndFirst[1];
                        user->lastName = lastAndFirst[0];
                    }

                    if (json.contains("email") && json["email"].isString())
                        user->eMail = json["email"].toString();

                    if (json.contains("clearance") && json["clearance"].isDouble())
                        user->clearance = json["clearance"].toInt();

                    emit loggedIn(true);
                }
            }
        }

        reply->deleteLater();
    });
}

void netManager::downloadFile(const char* key, const QString& path)
{
    setRequest(key);
    auto* reply = get(rqst);
    setCallback(reply,
                [path](const QByteArray& bytes)
    {
        QSaveFile file(path);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(bytes);
            file.commit();
        }
        else
            qDebug() << "file error :" << file.errorString();
    });
}

void netManager::getFromKey(const char* key,
                        const std::function<void(const QByteArray&)>& callback)
{
    setRequest(key);
    auto* reply = get(rqst);
    setCallback(reply, callback);
}

void netManager::putToKey(const char* key,
                      const QByteArray &data,
                      const std::function<void (const QByteArray &)> &callback)
{
    setRequest(key);
    auto* reply = put(rqst, data);
    setCallback(reply, callback);
}

void netManager::postToKey(const char* key,
                       const QByteArray &data,
                       const std::function<void (const QByteArray &)> &callback)
{
    setRequest(key);
    auto* reply = post(rqst, data);
    setCallback(reply, callback);
}

void netManager::setCallback(QNetworkReply* reply,
                         const std::function<void (const QByteArray &)> &callback)
{
    connect(reply, &QNetworkReply::finished,
            [reply, callback]()
    {
        callback(reply->readAll());
        reply->deleteLater();
    });
}

void netManager::setRequest(const char* key)
{
    QUrl url{prefix + key + '?'
                + '&' + suffix};

    rqst.setUrl(url);
}

}
