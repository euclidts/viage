#include "s_company.hpp"

namespace Data
{
s_company::s_company()
    : company_item{}
{
}

const std::string s_company::insert() const
{
    if (name == "")
        return {};

    return "INSERT INTO Company "
           "(Name) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + name +
            "') ";
}

void s_company::read(const nanodbc::result &res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Name"))
            name = res.get<std::string>("Name");
    }
    catch (...) {}
}

}
