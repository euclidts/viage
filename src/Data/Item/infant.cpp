#include <QVariant>

#include "infant.hpp"

namespace Data
{
namespace People
{
infant::infant()
    : base_item<infant>{}
    , person{}
    , sex{senior_citizen::M}
{}

QHash<int, QByteArray> infant::roleNames()
{
    QHash<int, QByteArray> names = person::roleNames();

    names[SexRole] = "sex";

    return names;
}

QVariant infant::data(int role) const
{
    QVariant base_data{person::data(role)};

    if (base_data != QVariant{})
        return base_data;

    if (role == SexRole)
        return sex;

    return QVariant{};
}

void infant::setData(const QVariant& value, int role)
{
    person::setData(value, role);

    if (role == SexRole)
        sex = senior_citizen::sexes(value.toInt());
}

void infant::read(const QJsonObject& json)
{
    person::read(json);

    if (json.contains("sex") && json["sex"].isDouble())
        sex = senior_citizen::sexes(json["sex"].toInt());
}

void infant::write(QJsonObject& json) const
{
    person::write(json);

    json["sex"] = sex;
}

bool infant::is_completed() const
{
    if (!person::is_completed())
        return false;

    return true;
}

}
}
