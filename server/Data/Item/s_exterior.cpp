#include "s_exterior.hpp"

namespace Data
{
namespace Places
{
s_exterior::s_exterior()
    : exterior_item{}
{
}

void s_exterior::set(const Row &row)
{
    try
    {
        if (!row["HasParking"].isNull())
            hasParking = row["HasParking"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["ParkingSpots"].isNull())
            parkingSpots = row["ParkingSpots"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["ParkingType"].isNull())
            parkingType = parkingTypes(row["ParkingType"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["ParkingSurface"].isNull())
            parkingSurface = row["ParkingSurface"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["TerrainDescription"].isNull())
            terrainDescription = row["TerrainDescription"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["TerrainSurface"].isNull())
            terrainSurface = row["TerrainSurface"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Rating"].isNull())
            rating = row["Rating"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Equipements"].isNull())
            equipement = equipements(row["Equipements"].as<int>());
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

void s_exterior::select_updated(std::string &query, const s_account* acnt)
{
    if (!acnt) return;
    query.append("a.State");
    acnt->select_updated(query, acnt);
}

void s_exterior::update_reply(const Result& res, Value& json, const s_account* acnt)
{
    acnt->update_reply(res, json);
}

}
}
