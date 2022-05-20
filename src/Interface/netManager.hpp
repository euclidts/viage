#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <wobjectdefs.h>

#include <QObject>
#include <QNetworkAccessManager>
#include <QSslConfiguration>

namespace Data
{
namespace People
{
struct user_item;
}
}

namespace Interface
{
class netManager final : public QNetworkAccessManager
{
    W_OBJECT(netManager)

public:
    netManager(const QString& url,
               const QString& authentication_arguments,
               const QString& extra_arguments);

    void authenticate(const QString& username, const QString& password);

    void loggedIn(const bool& success)
    W_SIGNAL(loggedIn, success);

    void downloadFile(const char* key, const QString& path);
    void getFromKey(const char* key,
                    const std::function<void (const QByteArray &)> &callback);
    void putToKey(const char* key,
                  const QByteArray& data,
                  const std::function<void (const QByteArray &)> &callback);
    void postToKey(const char* key,
                   const QByteArray& data,
                   const std::function<void (const QByteArray &)> &callback);

private:
    QNetworkRequest rqst;
    const QString prefix;
    QString auth_args;
    QString suffix;

    QString sessionId{""};
    Data::People::user_item* user;
    void setCallback(QNetworkReply* reply,
                     const std::function<void (const QByteArray &)> &callback);
    void setRequest(const char* key);

    bool authenticating{false};
};

}
#endif // NETMANAGER_HPP