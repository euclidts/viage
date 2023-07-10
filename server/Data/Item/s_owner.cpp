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

void s_owner::set(const Row &row)
{
    s_infant::set(row);

    try
    {
        if (!row["BirthDay"].isNull())
            birthDay = server_utils::from_db_date(row["BirthDay"].as<std::string>());
    }
    catch (...) {}

    try
    {
        if (!row["CivilStatus"].isNull())
            civilStatus = civilStates(row["CivilStatus"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["AVS"].isNull())
            avs = row["AVS"].as<std::string>();
    }
    catch (...) {}

    ads.set(row);
}

const std::string s_owner::insert(const s_user& usr, const s_account* acnt) const
{
    std::string str{"INSERT INTO Owner "
                    "(Sex, accountId) "
                    "VALUES("
                    + std::to_string(sex) +
                ", "
                + std::to_string(acnt->id) +
                ") "
                "RETURNING Id; "};

    acnt->foreign_update(str, acnt);

    return str;
}

const std::string s_owner::select(const s_user& usr, const s_account* acnt) const
{
    return search(usr, acnt) + " AND b.Id = " + std::to_string(id);
}

const std::string s_owner::update(const s_user& usr, const s_account* acnt) const
{
    return "UPDATE Owner SET "
            + s_infant::fields() +
            ", BirthDay = '"
           + server_utils::to_db_date(birthDay) +
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

const std::string s_owner::remove(const s_user &usr, const s_account *acnt) const
{
    return "DELETE FROM Owner WHERE Id = "
            + std::to_string(id);
}

void s_owner::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    std::string str{server_utils::update_flag(
                    account_item::OwnersCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_owner::select_updated(std::string &query, const s_account *acnt)
{
    if (!acnt) return;
    query.append("a.State");
    acnt->select_updated(query, acnt);
}

void s_owner::update_reply(const Result& res, Value& json, const s_account* acnt)
{
    acnt->update_reply(res, json);

    try
    {
        if (!res.front()["Acronym"].isNull())
            json["acronym"] = res.front()["Acronym"].as<std::string>();
    }
    catch (...) {}
}

}
}
