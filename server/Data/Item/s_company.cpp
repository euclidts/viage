#include "s_company.hpp"

namespace Data
{
s_company::s_company()
    : company_item{}
{
}

const std::string s_company::insert(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    if (name == "")
        return {};

    return "INSERT INTO Company "
           "(Name) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + name +
            "') ";
}

const std::string s_company::select(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return "";

    return "SELECT * FROM Company WHERE Id = "
            + std::to_string(id);
}

void s_company::set(const Row& row)
{
    try
    {
        if (!row["Id"].isNull())
            id = row["Id"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Name"].isNull())
            name = row["Name"].as<std::string>();
    }
    catch (...) {}
}

const std::string s_company::update(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "UPDATE Company SET "
           "Name = '"
            + name +
            "' WHERE Id = "
            + std::to_string(id);
}

}
