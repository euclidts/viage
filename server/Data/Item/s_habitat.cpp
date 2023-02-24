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

void s_habitat::set(const nanodbc::result& res)
{
    ads.set(res);

    try
    {
        if (!res.is_null("HabitatType"))
            habitatType = habitatTypes(res.get<int>("HabitatType"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Rooms"))
            rooms = res.get<int>("Rooms");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("RawSurface"))
            rawSurface = res.get<int>("RawSurface");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Surface"))
            surface = res.get<int>("Surface");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("M2Constructed"))
            m2Constructed = res.get<int>("M2Constructed");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("M2Available"))
            m2Available = res.get<int>("M2Available");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("M3s"))
            m3s = res.get<int>("M3s");
    }
    catch (...) {}
}

const string s_habitat::insert(const People::s_user& usr, s_account* acnt) const
{
    return "";
}

const string s_habitat::update(const People::s_user& usr, s_account* acnt) const
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

void s_habitat::foreign_update(std::string& query, bool complete, s_account* acnt)
{
    std::string str{server::utils::update_flag(
                    account_item::HabitatCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_habitat::condition(std::string &query, const People::s_user &usr, s_account *acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_habitat::update_reply(nanodbc::result& res, Value& json, s_account *acnt)
{
    acnt->update_reply(res, json);
}

}
}
