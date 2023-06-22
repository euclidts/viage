#include "s_habitat.hpp"

namespace Data
{
namespace Places
{
s_habitat::s_habitat()
    : habitat_item{}
    , ads{address}
{
}

void s_habitat::set(const Row &row)
{
    ads.set(row);

    try
    {
        if (!row["HabitatType"].isNull())
            habitatType = habitatTypes(row["HabitatType"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["Rooms"].isNull())
            rooms = row["Rooms"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["RawSurface"].isNull())
            rawSurface = row["RawSurface"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Surface"].isNull())
            surface = row["Surface"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["M2Constructed"].isNull())
            m2Constructed = row["M2Constructed"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["M2Available"].isNull())
            m2Available = row["M2Available"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["M3s"].isNull())
            m3s = row["M3s"].as<int>();
    }
    catch (...) {}
}

const std::string s_habitat::insert(const People::s_user& usr, const s_account* acnt) const
{
    return {};
}

const std::string s_habitat::select(const People::s_user &usr, const s_account *acnt) const
{
    return search(usr, acnt);
}

const std::string s_habitat::update(const People::s_user& usr, const s_account* acnt) const
{
    return "UPDATE Account SET "
            + ads.fields() +
            " , HabitatType = "
            + std::to_string(habitatType) +
            " , Rooms = "
            + std::to_string(rooms) +
            " , RawSurface = "
            + std::to_string(rawSurface) +
            " , Surface = "
            + std::to_string(surface) +
            " , M2Constructed = "
            + std::to_string(m2Constructed) +
            " , M2Available = "
            + std::to_string(m2Available) +
            " , M3s = "
            + std::to_string(m3s) +
            " WHERE Id = "
            + std::to_string(acnt->id);
}

void s_habitat::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    std::string str{server_utils::update_flag(
                    account_item::HabitatCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_habitat::condition(std::string &query, const People::s_user &usr, const s_account* acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_habitat::select_updated(std::string& query, const s_account* acnt)
{
    if (!acnt) return;
    query.append("a.State");
    acnt->select_updated(query, acnt);
}

void s_habitat::update_reply(const Result& res, Value& json, const s_account* acnt)
{
    acnt->update_reply(res, json);
}

}
}
