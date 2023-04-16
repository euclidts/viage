#include "s_team.hpp"

namespace Data
{
s_team::s_team()
    : team_item{}
{
}

const std::string s_team::insert(const People::s_user& usr, const s_company* foreign) const
{
    if (usr.clearance < People::s_user::Administrator) return {};
    if (caption == "" || foreign) return {};
    if (!foreign) return {};

    return "INSERT INTO Team "
           "(Caption, CompanyId) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + caption +
            "', '"
            + std::to_string(foreign->id) +
            "') ";
}

const std::string s_team::select(const People::s_user& usr, const s_company* foreign) const
{
    if (usr.clearance < People::s_user::Administrator && !foreign) return "";

    return "SELECT * FROM Team WHERE Id = "
           + std::to_string(id);
}

const std::string s_team::update(const People::s_user& usr, const s_company* foreign) const
{
    if (usr.clearance < People::s_user::Administrator) return {};

    return "UPDATE Company SET "
           "caption = '"
            + caption +
            "' WHERE Id = "
            + std::to_string(id);
}

const std::string s_team::remove(const People::s_user &usr, const s_company *foreign) const
{
    return {};
}

void s_team::set(const Row& row)
{
    try
    {
        if (!row["Id"].isNull())
            id = row["Id"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Caption"].isNull())
            caption = row["Caption"].as<std::string>();
    }
    catch (...) {}
}

void s_team::read(const Json::Value &json)
{
    team_item::read(json);

    if (json.isMember("CompanyId") && json["CompanyId"].isInt())
        companyId = json["CompanyId"].asInt();
}

}
