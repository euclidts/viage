#include <QVariant>

#include "infant_item.hpp"

namespace Data
{
namespace People
{
infant_item::infant_item()
    : person_item()
{
}

QHash<int, QByteArray> infant_item::roleNames()
{
    QHash<int, QByteArray> names = person_item::roleNames();

    names[SexRole] = "sex";

    return names;
}

QVariant infant_item::data(int role) const
{
    QVariant base_data{person_item::data(role)};

    if (base_data != QVariant())
        return base_data;

    if (role == SexRole)
        return QVariant(sex);

    return QVariant();
}

void infant_item::setData(const QVariant &value, int role)
{
    person_item::setData(value, role);

    if (role == SexRole)
        sex = senior_citizen_item::sexes(value.toInt());
}

void infant_item::read(const QJsonObject& json)
{
    person_item::read(json);

    if (json.contains("sex") && json["sex"].isDouble())
        sex = senior_citizen_item::sexes(json["sex"].toInt());
}

void infant_item::write(QJsonObject& json) const
{
    person_item::write(json);

    json["sex"] = sex;
}

bool infant_item::is_completed() const
{
    if (!person_item::is_completed())
        return false;

    return true;
}

}
}
