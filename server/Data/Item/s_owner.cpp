#include "s_owner.hpp"
#include "s_account.hpp"
#include <s_list.hpp>

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

void s_owner::set(const nanodbc::result& res)
{
    s_infant::set(res);

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

    ads.set(res);
}

const string s_owner::insert(const s_user& usr, s_account* acnt) const
{
    std::string str{"INSERT INTO BaseOwner "
                    "(OwnerType, Sex, OwnerAccountId) "
                    "OUTPUT inserted.id "
                    "VALUES('Owner', "
                    + std::to_string(sex) +
                ", "
                + std::to_string(acnt->id) +
                "); "};

    acnt->foreign_update(str, acnt);
    acnt->condition(str, usr, acnt);

    return str;
}

const string s_owner::update(const s_user& usr, s_account* acnt) const
{
    return "UPDATE BaseOwner SET "
            + s_infant::fields() +
            " , BirthDay = '"
            + birthDay +
            "' , CivilStatus = "
            + std::to_string(civilStatus) +
            " , AVS = '"
            + avs +
            "' WHERE Id = "
            + std::to_string(id) +
            "; ";
}

void s_owner::foreign_update(std::string& query, s_list<s_owner>* list, s_account* acnt)
{
    std::string str{};

    if (list->is_completed())
        str.append(", State |= " + std::to_string(account_item::OwnersCompleted));

    acnt->foreign_update(str, acnt);

    query.append(str);
}

void s_owner::condition(std::string& query, const s_user& usr, s_account* acnt)
{
    acnt->condition(query, usr, acnt);
}

const constexpr std::string s_owner::select(
        const s_user& usr, s_account* acnt)
{
    return "SELECT "
           "b.Id, "
           "b.FirstName, "
           "b.LastName, "
           "b.Sex, "
           "b.Phone, "
           "b.EMail, "
           "b.IsInfant, "
           "FROM Account a, "
           "BaseOwner b, "
           "[User] u "
           "WHERE b.InfantAccountId = "
            + std::to_string(acnt->id) +
            " AND b.OwnerType = 'Owner' "
            + server::utils::clearance_close(usr);
}

}
}
