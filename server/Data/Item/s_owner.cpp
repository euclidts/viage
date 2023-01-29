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
    const auto date{trantor::Date::date().toDbStringLocal()};

    std::string str{"INSERT INTO BaseOwner "
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
                + std::to_string(acnt->id)};

    acnt->enclose_condition(str, usr, acnt);

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
            + std::to_string(id);
}

}
}
