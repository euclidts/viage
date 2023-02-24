#include <Item/habitat_item.hpp>

namespace Data
{
namespace Places
{
habitat_item::habitat_item()
    : base_data{}
    , address{new address_item{}}
{
}

void habitat_item::read(const Json::Value& json)
{
    if (json.isMember("address") && json["address"].isObject())
        address->read(json["address"]);

    if (json.isMember("habitatType") && json["habitatType"].isInt())
        habitatType = habitatTypes(json["habitatType"].asInt());

    if (json.isMember("rooms") && json["rooms"].isInt())
        rooms = json["rooms"].asInt();

    if (json.isMember("rawSurface") && json["rawSurface"].isInt())
        rawSurface = json["rawSurface"].asInt();

    if (json.isMember("surface") && json["surface"].isInt())
        surface = json["surface"].asInt();

    if (json.isMember("m2Constructed") && json["m2Constructed"].isInt())
        m2Constructed = json["m2Constructed"].asInt();

    if (json.isMember("m2Available") && json["m2Available"].isInt())
        m2Available = json["m2Available"].asInt();

    if (json.isMember("m3s") && json["m3s"].isInt())
        m3s = json["m3s"].asInt();
}

void habitat_item::write(Json::Value& json) const
{
    Json::Value jsonAddress;
    address->write(jsonAddress);

    json["address"] = jsonAddress;
    json["habitatType"] = habitatType;
    json["rooms"] = rooms;
    json["rawSurface"] = rawSurface;
    json["surface"] = surface;
    json["m2Constructed"] = m2Constructed;
    json["m2Available"] = m2Available;
    json["m3s"] = m3s;
}

bool habitat_item::is_completed() const
{
    if (habitatType == habitatTypes::None)
        return false;

    if (!address->is_completed())
        return false;

    return true;
}

}
}
