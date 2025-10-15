#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <QObject>
#include <QSaveFile>
#include <QNetworkAccessManager>
#ifndef EMSCRIPTEN
#include <QSslConfiguration>
#endif

#include <wobjectdefs.h>

namespace Interface
{
class smtp;

class netManager final : public QNetworkAccessManager
{
    W_OBJECT(netManager)

public:
    static netManager& instance();

    void init(const QString& url);
protected:
    void init();
public:

    netManager(netManager const&) = delete;
    void operator = (netManager const&) = delete;

    void authenticate(const QString& username, const QString& password);

    void loggedIn(bool success,
                  const QString& errorString = "")
    W_SIGNAL(loggedIn, success, errorString)

    void replyError(const QString& prefix = "",
                    const QString& errorString = "")
    W_SIGNAL(replyError, prefix, errorString)

    void downloadFile(const char* key,
                      const QString& path,
                      const std::function<void (bool, const QString &)> &callback,
                      const std::function<void (qint64, qint64)>& onProgress = [](qint64 byteSent, qint64 totalBytes){});
    void downloadFilePost(const char* key,
                        const QByteArray &postData,
                        const QString &path,
                        const std::function<void (bool, const QString &)> &callback,
                        const std::function<void (qint64, qint64)>& onProgress);
    void getFromKey(const char* key,
                    const std::function<void (const QByteArray &)> &callback,
                    const char* params = "");
    void putToKey(const char* key,
                  const QByteArray& data,
                  const std::function<void (const QJsonObject &)> &callback,
                  const QString& errorPrefix = "",
                  const std::function<void ()>& errorCallback = [](){},
                  const std::function<void (qint64, qint64)>& onProgress = [](qint64 byteSent, qint64 totalBytes){});
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

    QString getPrefix(){
        return prefix;
    }
private:
    netManager() {}

    QString prefix;
    QNetworkRequest rqst{};
    QString suffix = "format=json&jsconfig=TreatEnumAsInteger";

    void setCallback(QNetworkReply* reply,
                     const std::function<void (const QByteArray &)> &callback);
    void setCallback(QNetworkReply* reply,
                     const std::function<void (const QJsonObject &)> &callback,
                     const QString& errorPrefix,
                     const std::function<void ()>& errorCallback = [](){});

    void setRequest(const char* key, const char* params = "");

    bool authenticating{false};
};

}
#endif // NETMANAGER_HPP
