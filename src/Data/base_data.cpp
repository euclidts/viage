#include <QJsonDocument>
#include <QJsonObject>
#include <wobjectimpl.h>

#include "base_data.hpp"

namespace Data {
W_OBJECT_IMPL(base_data)

base_data::base_data(QObject* parent)
    : QObject{parent}
{
}

const QByteArray base_data::toData(const char* parentKey, int parentId)
{
    QString str{parentKey};
    str.append("Id");

    QJsonObject data{ {str, parentId} };

    writeWithKey(data);

    QJsonDocument bytes{data};
    return bytes.toJson();
}

const QByteArray base_data::toData(int parentId)
{
    QJsonObject data{ {"Id", parentId} };

    writeWithKey(data);

    QJsonDocument bytes{data};
    return bytes.toJson();
}
}
