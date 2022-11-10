#include "infant_item.hpp"

namespace Data
{
namespace People
{
infant_item::infant_item()
    : person_item()
{
}

void infant_item::read(const Json::Value& json)
{
    person_item::read(json);

    if (json.isMember("sex") && json["sex"].isInt())
        sex = senior_citizen_item::sexes(json["sex"].asInt());
}

void infant_item::write(Json::Value &json) const
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
