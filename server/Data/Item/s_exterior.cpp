#include "s_exterior.hpp"

namespace Data
{
namespace Places
{
s_exterior::s_exterior()
    : exterior_item{}
{
}

void s_exterior::set(const nanodbc::result& res)
{
    try
    {
        if (!res.is_null("HasParking"))
            hasParking = res.get<int>("HasParking");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ParkingSpots"))
            parkingSpots = res.get<int>("ParkingSpots");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ParkingType"))
            parkingType = parkingTypes(res.get<int>("ParkingType"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ParkingSurface"))
            parkingSurface = res.get<int>("ParkingSurface");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("TerrainDescription"))
            terrainDescription = res.get<std::string>("TerrainDescription");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("TerrainSurface"))
            terrainSurface = res.get<int>("TerrainSurface");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Rating"))
            rating = res.get<int>("Rating");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Equipements"))
            equipement = equipements(res.get<int>("Equipements"));
    }
    catch (...) {}
}

const std::string s_exterior::insert(const People::s_user& usr, const s_account* acnt) const
{
    return "";
}

const std::string s_exterior::select(const People::s_user &usr, const s_account *acnt) const
{
    return search(usr, acnt);
}

const std::string s_exterior::update(const People::s_user& usr, const s_account* acnt) const
{
    return "UPDATE Account SET "
            "HasParking = "
            + std::to_string(hasParking) +
            " , ParkingSpots = "
            + std::to_string(parkingSpots) +
            " , ParkingType = "
            + std::to_string(parkingType) +
            " , ParkingSurface = "
            + std::to_string(parkingSurface) +
            " , TerrainDescription = '"
            + terrainDescription +
            "' , TerrainSurface = "
            + std::to_string(terrainSurface) +
            " , Rating = "
            + std::to_string(rating) +
            " , Equipements = "
            + std::to_string(equipement) +
            " WHERE Id = "
            + std::to_string(acnt->id);
}

void s_exterior::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    std::string str{server::utils::update_flag(
                    account_item::ExteriorCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_exterior::condition(std::string &query, const People::s_user& usr, const s_account* acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_exterior::update_reply(nanodbc::result& res, Value& json, const s_account* acnt)
{
    acnt->update_reply(res, json);
}

}
}
