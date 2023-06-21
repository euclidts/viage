#include <QNetworkReply>
#include <QNetworkRequest>

#include <wobjectimpl.h>

#include "netManager.hpp"

namespace Interface
{
W_OBJECT_IMPL(netManager)

netManager& netManager::instance()
{
    static netManager instance;
    return instance;
}

void netManager::init(const QString& url,
                       const QString& authentication_arguments,
                       const QString& extra_arguments)
{
    rqst = {};
    prefix = url + '/';
    auth_args = authentication_arguments;
    suffix = extra_arguments;

    auto conf = QSslConfiguration::defaultConfiguration();
    rqst.setSslConfiguration(conf);
    rqst.setHeader(QNetworkRequest::ContentTypeHeader,
                   "application/json");

    setTransferTimeout();

    connect(this, &QNetworkAccessManager::sslErrors,
            this, [](QNetworkReply* reply,
            const QList<QSslError>& errors)
    { reply->ignoreSslErrors(errors); });

    connect(this, &QNetworkAccessManager::finished,
            this, [this](QNetworkReply* reply)
    {
        if (reply->error() != QNetworkReply::NoError)
            emit replyError("netManager reply error",
                            reply->errorString());
    });
}

using namespace Json;

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
                emit loggedIn(false, reply->errorString());
            }
        }
        else
        {
            const auto res = reply->readAll();
            Value json;
            Reader reader;
            reader.parse(res.toStdString(), json);

            if (json.isMember("sessionId"))
            {
                if (authenticating)
                {
                    authenticating = false;

                    if (json.isMember("sessionId") && json["sessionId"].isString())
                    {
                        const auto str{json["sessionId"].asString()};
                        rqst.setRawHeader("sessionId",
                                          QByteArray::fromStdString(str));
                    }

                    if (json.isMember("id") && json["id"].isDouble())
                        emit userChanged(json["id"].asInt());

                    if (json.isMember("clearance") && json["clearance"].isDouble())
                        emit clearanceChanged(json["clearance"].asInt());

                    emit loggedIn(true);
                }
            }
        }

        reply->deleteLater();
    });
}

void netManager::downloadFile(const char* key,
                              const QString &path,
                              const std::function<void (bool, const QString &)> &callback,
                              const std::function<void (qint64, qint64)>& onProgress)
{
    setRequest(key);
    auto* reply = get(rqst);
    setCallback(reply,
                [path, callback](const QByteArray& bytes)
    {
        if (bytes.isValidUtf8())
        {
            qDebug() << QString(bytes);
            callback(false, QString(bytes));
            return;
        }

        QSaveFile file(path);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(bytes);
            if (file.commit())
                callback(true, "");
            else
                callback(false, file.errorString());
        }
        else
            callback(false, file.errorString());
    });

    connect(reply,
            &QNetworkReply::uploadProgress,
            onProgress);
}

void netManager::getFromKey(const char* key,
                            const std::function<void (const QByteArray &)> &callback, const char *params)
{
    setRequest(key);
    auto* reply = get(rqst);
    setCallback(reply, callback);
}

void netManager::putToKey(const char* key,
                          const QByteArray& data,
                          const std::function<void (const Value &)>& callback,
                          const QString& errorPrefix,
                          const std::function<void ()>& errorCallback,
                          const std::function<void (qint64, qint64)>& onProgress)
{
    setRequest(key);
    auto* reply = put(rqst, data);
    setCallback(reply, callback, errorPrefix, errorCallback);

    connect(reply,
            &QNetworkReply::uploadProgress,
            onProgress);
}

void netManager::postToKey(const char* key,
                           const QByteArray &data,
                           const std::function<void (const Value &)> &callback,
                           const QString& errorPrefix)
{
    setRequest(key);
    auto* reply = post(rqst, data);
    setCallback(reply, callback, errorPrefix);
}

void netManager::deleteToKey(const char *key,
                             const QByteArray &data,
                             const std::function<void (const Value &)> &callback,
                             const QString& errorPrefix)
{
    setRequest(key);
    auto* reply = sendCustomRequest(rqst, "DELETE", data);
    setCallback(reply, callback, errorPrefix);
}

void netManager::setCallback(QNetworkReply* reply,
                             const std::function<void (const Value &)> &callback,
                             const QString& errorPrefix,
                             const std::function<void ()>& errorCallback)
{
    connect(reply, &QNetworkReply::finished,
            this,
            [reply, callback, errorPrefix, errorCallback, this]()
    {
        const auto res = reply->readAll();
        Value json;
        Reader reader;
        reader.parse(res.toStdString(), json);

        if (json.isMember("success"))
        {
            if (json["success"].asBool())
                callback(json);
            else
            {
                emit replyError(errorPrefix, QString::fromStdString(json["errorMessage"].asString()));
                errorCallback();
            }
        }
        else
        {
            emit replyError(errorPrefix);
            errorCallback();
        }

        reply->deleteLater();
    });
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

void netManager::setRequest(const char* key, const char * params)
{
    QUrl url{prefix + key + '?' + suffix + params};
    rqst.setUrl(url);
}

}
