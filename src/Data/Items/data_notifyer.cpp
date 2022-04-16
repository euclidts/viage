#include <QJsonDocument>
#include <QJsonObject>
#include <wobjectimpl.h>

#include "data_notifyer.hpp"

namespace Data {
W_OBJECT_IMPL(data_notifyer)

data_notifyer::data_notifyer(QObject *parent)
    : QObject{parent}
{
}

const QByteArray data_notifyer::toData(const char* parentKey, int parentId)
{
    QJsonObject json{};
    write(json);

    QString str{parentKey};
    str.append("Id");

    QJsonObject data{
        {str, parentId},
        {key(), json}
    };

    QJsonDocument bytes{data};
    return bytes.toJson();
}

}
