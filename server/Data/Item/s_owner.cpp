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
            birthDay = server::utils::from_db_date(res.get<std::string>("BirthDay"));
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
            ", BirthDay = '"
            + server::utils::to_db_date(birthDay) +
            "', CivilStatus = "
            + std::to_string(civilStatus) +
            ", AVS = '"
            + avs +
            "', "
            + ads.fields() +
            " WHERE Id = "
            + std::to_string(id) +
            "; ";
}

void s_owner::foreign_update(std::string& query, bool complete, s_account* acnt)
{
    std::string str{" OUTPUT inserted.Acronym "};

    if (complete)
    {
        str.insert(0,
                   ", State |= "
                   + std::to_string(account_item::OwnersCompleted));

        str.append(", inserted.State ");
    }

    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_owner::condition(std::string& query, const s_user& usr, s_account* acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_owner::update_reply(nanodbc::result& res, Value& json, s_account* acnt)
{
    acnt->update_reply(res, json);

    try
    {
        if (!res.is_null("Acronym"))
            json["acronym"] = res.get<std::string>("Acronym");
    }
    catch (...) {}
}

}
}
