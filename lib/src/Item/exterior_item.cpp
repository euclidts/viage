#include <Item/exterior_item.hpp>

namespace Data
{
namespace Places
{
exterior_item::exterior_item()
    : base_data{}
{
}

void exterior_item::read(const Json::Value &json)
{
    if (json.isMember("hasParking") && json["hasParking"].isBool())
        hasParking = json["hasParking"].asBool();

    if (json.isMember("parkingSpots") && json["parkingSpots"].isInt())
        parkingSpots = json["parkingSpots"].asInt();

    if (json.isMember("parkingType") && json["parkingType"].isInt())
        parkingType = parkingTypes(json["parkingType"].asInt());

    if (json.isMember("parkingSurface") && json["parkingSurface"].isInt())
        parkingSurface = json["parkingSurface"].asInt();

    if (json.isMember("terrainDescription") && json["terrainDescription"].isString())
        terrainDescription = json["terrainDescription"].asString();

    if (json.isMember("terrainSurface") && json["terrainSurface"].isInt())
        terrainSurface = json["terrainSurface"].asInt();

    if (json.isMember("rating") && json["rating"].isInt())
        rating = json["rating"].asInt();

    if (json.isMember("equipements") && json["equipements"].isInt())
        equipement = equipements(json["equipements"].asInt());
}

void exterior_item::write(Json::Value &json) const
{
    json["hasParking"] = hasParking;
    if (hasParking)
    {
        json["parkingSpots"] = parkingSpots;
        json["parkingType"] = parkingType;
        json["parkingSurface"] = parkingSurface;
    }
    json["terrainDescription"] = terrainDescription;
    json["terrainSurface"] = terrainSurface;
    json["equipements"] = equipement;
    json["rating"] = rating;
}

bool exterior_item::is_completed() const
{
    if(rating == 0)
        return false;

    return true;
}

}
}
