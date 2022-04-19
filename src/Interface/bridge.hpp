#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <QObject>

#include <wobjectdefs.h>

namespace Interface
{
class bridge final : public QObject
{
    W_OBJECT(bridge)

public:
    void loggedIn(const bool& success);

    void authenticate(const QString& username, const QString& password)
    W_SIGNAL(authenticate, username, password)

    void requestReport(const QUrl& path)
    W_SIGNAL(requestReport, path)

    void set_qmlObject(QObject* obj) { qmlObject = obj; }

private:
    QObject* qmlObject;
};

}

#endif // BRIDGE_HPP
