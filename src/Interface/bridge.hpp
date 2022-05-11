#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <QObject>

#include <wobjectdefs.h>

namespace Interface
{
class netManager;

class bridge final : public QObject
{
    W_OBJECT(bridge)

public:
    bridge(Interface::netManager* manager);
    void onLogin(const bool& success);

    void authenticate(const QString& username, const QString& password);
    W_INVOKABLE(authenticate, (const QString&, const QString&))

    void downloadFile(const QString& key, const QString& path);
    W_INVOKABLE(downloadFile, (const QString&, const QString&))

    void requestReport(const QUrl& directory);
    W_INVOKABLE(requestReport, (const QUrl&))

    void setQmlObject(QObject* obj) { qmlObject = obj; }

private:
    QObject* qmlObject;

    netManager* mng;
};

}

#endif // BRIDGE_HPP
