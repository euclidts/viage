#include "s_contact.hpp"

namespace Data
{
namespace People
{
s_contact::s_contact()
    : contact_item{}
    , s_infant{}
{
}

void s_contact::read(const nanodbc::result& res)
{
    s_infant::read(res);

    try
    {
        if (!res.is_null("IsInfant"))
            isInfant = res.get<int>("IsInfant");
    }
    catch (...) {}
}

const string s_contact::insert(const s_user& usr, s_account* acnt) const
{
    const auto date{trantor::Date::date().toDbStringLocal()};

    return "IF EXISTS "
           "(SELECT "
           "a.Id "
           "FROM Account a, "
           "[User] u, "
           "Company c "
           "WHERE a.Id = "
            + std::to_string(acnt->id) +
            "AND u.id = a.AdvisorId "
            "AND c.id = u.CompanyId "
            "AND u.TeamId = 2) "
            + server::utils::clearance_close(usr) +
            " BEGIN "
            "INSERT INTO BaseOwner "
            "(OwnerType, Sex, InfantAccountId) "
            "OUTPUT inserted.id "
            "VALUES('Contact', "
            + std::to_string(sex) +
            ", "
            + std::to_string(acnt->id) +
            "); UPDATE Account "
            "SET UpdateDate = '"
            + date +
            "' WHERE Id = "
            + std::to_string(acnt->id) +
            " END ";
}

const string s_contact::update(const s_user& usr, s_contact* acnt) const
{
    const auto date{trantor::Date::date().toDbStringLocal()};

    return "IF EXISTS "
           "(SELECT "
           "a.Id "
           "FROM Account a, "
           "[User] u, "
           "Company c "
           "WHERE a.Id = "
            + std::to_string(acnt->id) +
            "AND u.id = a.AdvisorId "
            "AND c.id = u.CompanyId "
            "AND u.TeamId = 2) "
            + server::utils::clearance_close(usr) +
            " BEGIN "
            "INSERT INTO BaseOwner "
            "(OwnerType, Sex, InfantAccountId) "
            "OUTPUT inserted.id "
            "VALUES('Contact', "
            + std::to_string(sex) +
            ", "
            + std::to_string(acnt->id) +
            "); UPDATE Account "
            "SET UpdateDate = '"
            + date +
            "' WHERE Id = "
            + std::to_string(acnt->id) +
            " END ";
}

}
}
