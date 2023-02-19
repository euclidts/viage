#include "s_account.hpp"
#include <s_list.hpp>

namespace Data
{
s_account::s_account()
    : account_item{}
{
}

const std::string s_account::insert(const People::s_user& usr) const
{
    const auto creation_date{trantor::Date::date().toDbStringLocal()};

    return "SET NOCOUNT ON "
           "DECLARE @table table (id int) "
           "INSERT INTO Account "
           "(CreationDate, UpdateDate, AdvisorId, State, HabitatType) "
           "OUTPUT inserted.id INTO @table "
           "VALUES ('"
            + creation_date +
            "', '"
            + creation_date +
            "', "
            + std::to_string(usr.id) +
            ", 0, 0) "
            "DECLARE @id int "
            "SELECT @id = id FROM @table "
            "INSERT INTO BaseOwner "
            "(OwnerType, Sex, OwnerAccountId) "
            "OUTPUT @id Id "
            "VALUES ('Owner', 0, @id) ";
}

const std::string s_account::update(const People::s_user& usr) const
{
    return {};
}

void s_account::set(nanodbc::result& res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Acronym"))
            acronym = res.get<std::string>("Acronym");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("CreationDate"))
            created = server::utils::from_db_date_time(res.get<std::string>("CreationDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("UpdateDate"))
            modified = server::utils::from_db_date_time(res.get<std::string>("UpdateDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("State"))
            state = states(res.get<int>("State"));
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
        if (!res.is_null("AdvisorFirstName"))
            advisorFirstName = res.get<std::string>("AdvisorFirstName");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("AdvisorLastName"))
            advisorLastName = res.get<std::string>("AdvisorLastName");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Name"))
            company = res.get<std::string>("Name");
    }
    catch (...) {}

    //    remove_multiple(res);
}

//void s_account::remove_multiple(nanodbc::result& res)
//{
//    int prev_id{res.get<int>("Id")};

//    if (!res.next())
//        return;

//    if (prev_id == res.get<int>("Id"))
//        remove_multiple(res);
//    else
//        res.prior();
//}

}
