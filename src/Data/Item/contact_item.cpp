#include <QVariant>

#include "contact_item.hpp"

namespace Data
{
namespace People
{
contact_item::contact_item()
    : infant_item()
{
}

QHash<int, QByteArray> contact_item::roleNames()
{
    QHash<int, QByteArray> names = infant_item::roleNames();

    names[IsInfantRole] = "isInfant";

    return names;
}

QVariant contact_item::data(int role) const
{
    QVariant base_data{infant_item::data(role)};

    if (base_data != QVariant())
        return base_data;

    if (role == IsInfantRole)
        return QVariant(isInfant);

    return QVariant();
}

void contact_item::setData(const QVariant &value, int role)
{
    infant_item::setData(value, role);

    if (role == IsInfantRole)
        isInfant = value.toBool();
}

void contact_item::read(const QJsonObject& json)
{
    infant_item::read(json);

    if (json.contains("isInfant") && json["isInfant"].isBool())
        isInfant = json["isInfant"].toBool();
}

void contact_item::write(QJsonObject& json) const
{
    infant_item::write(json);

    json["isInfant"] = isInfant;
}

bool contact_item::is_completed() const
{
    if (!infant_item::is_completed())
        return false;

    return true;
}

}
}
