#include <QDate>
#include <QUrl>

#include <wobjectimpl.h>

#include "bridge.hpp"
#include "netManager.hpp"

namespace Interface
{
W_OBJECT_IMPL(bridge)

bridge::bridge(Interface::netManager* manager)
    : mng{manager}
{
    connect(mng, &netManager::loggedIn,
            this, &bridge::onLogin);
}

void bridge::onLogin(const bool& success)
{
    QMetaObject::invokeMethod(qmlObject,
                              "onLogin",
                              Q_ARG(bool, success));
}

void bridge::authenticate(const QString &username, const QString &password)
{
    mng->authenticate(username, password);
}

void bridge::downloadFile(const QString& key, const QString& path)
{
    mng->downloadFile(key.toStdString().c_str(), path);
}

void bridge::requestReport(const QUrl &directory)
{
    auto now{QDateTime::currentDateTime()};

    auto fileName{directory.path()};
    fileName.append("/Viage-");
    fileName.append(now.toString("dd-MM-yy-hh-mm"));
    fileName.append(".xlsb");

    const auto fullPath{QUrl::fromLocalFile(fileName)};

    emit downloadFile("export/accounts", fullPath.toLocalFile());
}
}
