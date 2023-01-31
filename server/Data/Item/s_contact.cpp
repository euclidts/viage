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

void s_contact::set(const nanodbc::result& res)
{
    s_infant::set(res);

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

    std::string str{"INSERT INTO BaseOwner "
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
                + std::to_string(acnt->id)};

    acnt->condition(str, usr, acnt);

    return str;
}

const string s_contact::update(const s_user& usr, s_account* acnt) const
{
    return "UPDATE BaseOwner SET "
            + s_infant::fields() +
            " , IsInfant = "
            + std::to_string(isInfant) +
            " WHERE Id = "
            + std::to_string(id);
}

}
}