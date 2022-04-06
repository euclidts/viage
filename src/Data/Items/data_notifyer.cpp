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

const QByteArray data_notifyer::toData(int id)
{
    QJsonObject json{};
    write(json);

    QJsonObject data{
        {"id", id},
        {key(), json}
    };

    QJsonDocument bytes{data};
    return bytes.toJson();
}

}
