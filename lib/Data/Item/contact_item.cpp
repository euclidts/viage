#include "contact_item.hpp"

namespace Data
{
namespace People
{
contact_item::contact_item()
    : infant_item()
{
}

void contact_item::read(const Json::Value& json)
{
    infant_item::read(json);

    if (json.isMember("isInfant") && json["isInfant"].isBool())
        isInfant = json["isInfant"].asBool();
}

void contact_item::write(Json::Value &json) const
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
