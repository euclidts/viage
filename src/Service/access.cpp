#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

#include <wobjectimpl.h>

#include "access.hpp"
#include <Items/user_item.hpp>

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
                    user = new Data::People::user_item();
                    authenticating = false;

                    if (json.contains("sessionId") && json["sessionId"].isString())
                    {
                        const QString str{json["sessionId"].toString()};
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

void access::getReport(const QUrl &directory)
{
    setRequest("export/accounts");
    QNetworkReply* reply = get(rqst);
    setCallback(reply,
                [&directory](const QByteArray& bytes)
    {
        QDateTime now{QDateTime::currentDateTime()};

        QString fileName{directory.path()};
        fileName.append("/Viage-");
        fileName.append(now.toString("dd-MM-yy-hh-mm"));
        fileName.append(".xlsb");

        QSaveFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(bytes);
        file.commit();
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
    qDebug() << rqst.url() << data;
    QNetworkReply* reply = post(rqst, data);
    setCallback(reply, callback);
}

void access::postToKeyAs(const char *key, const std::function<void (const QByteArray &)> &callback)
{
    setRequest(key);

    QJsonObject json{ {"advisor", user->id} };
    QByteArray data{QJsonDocument{json}.toJson()};

    qDebug() << rqst.url() << data;
    QNetworkReply* reply = post(rqst, data);
    setCallback(reply, callback);
}

void access::setCallback(QNetworkReply* reply,
                         const std::function<void (const QByteArray &)> &callback)
{
    connect(reply, &QNetworkReply::finished,
            [=]()
    {
        const auto data = reply->readAll();
        qDebug() << data;
        callback(data);
//        callback(reply->readAll());
        reply->deleteLater();
    });
}

void access::setRequest(const char* key)
{
    QUrl url{prefix + key + '?'
                + '&' + suffix};

    rqst.setUrl(url);
}

}
