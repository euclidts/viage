#include "s_user.hpp"

namespace Data
{
namespace People
{
s_user::s_user()
    : user_item{}
    , s_person{}
    , sa{address}
    , last_access{trantor::Date::date()}
{
}

const std::string s_user::insert(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "INSERT INTO [User] "
           "(FirstName, LastName) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + user_item::firstName +
            "', '"
            + user_item::lastName +
            "') ";
}

const std::string s_user::update(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "UPDATE [User] SET "
            + fields() +
            " WHERE Id = "
            + std::to_string(id);
}

void s_user::read(const nanodbc::result& res)
{
    s_person::read(res);

    try
    {
        if (!res.is_null("Company"))
            company = res.get<std::string>("Company");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Clearance"))
            clearance = clearances(res.get<int>("Clearance"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Team"))
            team = res.get<std::string>("Team");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Beneficiary"))
            beneficiary = res.get<std::string>("Beneficiary");
    }
    catch (...) {}

    sa.read(res);

    try
    {
        if (!res.is_null("Iban"))
            iban = res.get<std::string>("Iban");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Bic"))
            bic = res.get<std::string>("Bic");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("CompanyId"))
            company_id = res.get<int>("CompanyId");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Name"))
            company = res.get<std::string>("Name");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("TeamId"))
            team_id = res.get<int>("TeamId");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Caption"))
            team = res.get<std::string>("Caption");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("IsLocked"))
            isLocked = res.get<int>("IsLocked");
    }
    catch (...) {}
}

const std::string s_user::fields() const
{
    return sa.fields() +
            ", "
            + s_person::fields() +
            ", CompanyId = "
            + std::to_string(company_id) +
            ", TeamId = "
            + std::to_string(team_id) +
            ", Beneficiary = '"
            + beneficiary +
            "', Iban = '"
            + iban +
            "', Bic = '"
            + bic +
            "'";
}

}
}
