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

void s_contact::set(const Row &row)
{
    s_infant::set(row);

    try
    {
        if (!row["IsInfant"].isNull())
            isInfant = row["IsInfant"].as<bool>();
    }
    catch (...) {}
}

const std::string s_contact::insert(const s_user& usr, const s_account* acnt) const
{
    const auto date{trantor::Date::date().toDbStringLocal()};

    std::string str{"INSERT INTO Contact "
                    "(OwnerType, Sex, AccountId) "
                    "OUTPUT inserted.id "
                    "VALUES('Contact', "
                    + std::to_string(sex) +
                ", "
                + std::to_string(acnt->id) +
                "); UPDATE Account "
                "SET UpdateDate = '"
                + date +
                "' WHERE Id = "
                + std::to_string(acnt->id)};

    return str;
}

const std::string s_contact::select(const s_user &usr, const s_account *acnt) const
{
    return search(usr, acnt) + " AND b.Id = " + std::to_string(id);
}

const std::string s_contact::update(const s_user& usr, const s_account* acnt) const
{
    return "UPDATE Contact SET "
            + s_infant::fields() +
            " , IsInfant = "
            + std::to_string(isInfant) +
            " WHERE Id = "
            + std::to_string(id);
}

const std::string s_contact::remove(const s_user &usr, const s_account *acnt) const
{
    return "DELETE FROM Contact WHERE Id = "
            + std::to_string(id);
}

void s_contact::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    std::string str{server::utils::update_flag(
                    account_item::ContactsCompleted,
                    "State",
                    complete)};
    acnt->foreign_update(str, complete, acnt);
    query.append(str);
}

void s_contact::condition(std::string &query, const s_user &usr, const s_account *acnt)
{
    acnt->condition(query, usr, acnt);
}

void s_contact::update_reply(const Result &res, Value& json, const s_account *acnt)
{
    acnt->update_reply(res, json);
}

}
}
