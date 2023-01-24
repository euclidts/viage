#include "s_owner.hpp"

namespace Data
{
namespace People
{
s_owner::s_owner()
    : owner_item{}
    , s_infant{}
    , ads{address}
{
}

void s_owner::read(const nanodbc::result& res)
{
    s_infant::read(res);

    try
    {
        if (!res.is_null("BirthDay"))
        {
            auto str = res.get<std::string>("BirthDay");
            str.erase(str.begin() + str.find_first_of('+') - 1, str.end());
            birthDay = str;
        }
    }
    catch (...) {}

    try
    {
        if (!res.is_null("CivilStatus"))
            civilStatus = civilStates(res.get<int>("CivilStatus"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("AVS"))
            avs = res.get<std::string>("AVS");
    }
    catch (...) {}

    ads.read(res);
}

const string s_owner::insert(const s_user& usr, s_account* acnt) const
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
            "AND u.TeamId = 2 "
            + server::utils::clearance_close(usr) +
            ") BEGIN "
            "INSERT INTO BaseOwner "
            "(OwnerType, Sex, OwnerAccountId) "
            "OUTPUT inserted.id "
            "VALUES('Owner', "
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

const string s_owner::update(const s_user& usr, s_account* acnt) const
{
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
            "AND u.TeamId = 2 "
            + server::utils::clearance_close(usr) +
            ") INSERT INTO BaseOwner "
            "(OwnerType, Sex, OwnerAccountId) "
            "OUTPUT inserted.id "
            "VALUES('Owner', "
            + std::to_string(sex) +
            ", "
            + std::to_string(acnt->id);
}

}
}
