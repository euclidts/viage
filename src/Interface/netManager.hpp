#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QSaveFile>

#include <wobjectdefs.h>

namespace Data
{
}

namespace Interface
{
class smtp;

class netManager final : public QNetworkAccessManager
{
    W_OBJECT(netManager)

public:
    netManager(const QString& url,
               const QString& authentication_arguments,
               const QString& extra_arguments);

    void authenticate(const QString& username, const QString& password);

    void loggedIn(const bool& success,
                  const QString& errorString = "")
    W_SIGNAL(loggedIn, success, errorString);

    void replyError(const QString& prefix = "",
                    const QString& errorString = "")
    W_SIGNAL(replyError, prefix, errorString);

    void downloadFile(const char* key,
                      const QString& path,
                      const std::function<void (bool, const QString &)> &callback);
    void getFromKey(const char* key,
                    const std::function<void (const QByteArray &)> &callback);
    void putToKey(const char* key,
                  const QByteArray& data,
                  const std::function<void (const QJsonObject &)> &callback,
                  const QString& errorPrefix = "");
    void postToKey(const char* key,
                   const QByteArray& data,
                   const std::function<void (const QJsonObject &)> &callback,
                   const QString& errorPrefix = "");
    void deleteToKey(const char* key,
                     const QByteArray& data,
                     const std::function<void (const QJsonObject &)> &callback,
                     const QString& errorPrefix = "");

    void userChanged(int newId)
    W_SIGNAL(userChanged, newId)

    void clearanceChanged(int newClearance)
    W_SIGNAL(clearanceChanged, newClearance)

private:
    QNetworkRequest rqst;
    const QString prefix;
    QString auth_args;
    QString suffix;

    void setCallback(QNetworkReply* reply,
                     const std::function<void (const QByteArray &)> &callback);
    void setCallback(QNetworkReply* reply,
                     const std::function<void (const QJsonObject &)> &callback,
                     const QString& errorPrefix);
    void setRequest(const char* key);

    bool authenticating{false};
};

}
#endif // NETMANAGER_HPP
