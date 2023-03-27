#include "s_account.hpp"
#include <server.hpp>

namespace Data
{
s_account::s_account()
    : account_item{}
{
}

void s_account::read(const Value& json)
{
    account_item::read(json);

    if (json.isMember("isPPE") && json["isPPE"].isBool())
        fields_set |= PpeSet;

    if (json.isMember("state") && json["state"].isInt())
        fields_set |= StateSet;
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

const std::string s_account::select(const People::s_user& usr) const
{
    return "SELECT "
           "State, "
           "IsPPE, "
           "ReceivedDate, "
           "TransmitedDate, "
           "ExpertizedDate, "
           "DecidedDate, "
           "NotarizedDate, "
           "PaidDate "
           "FROM Account WHERE Id = "
            + std::to_string(id);
}

const std::string s_account::update(const People::s_user& usr) const
{
    if (fields_set == None) return {};

    std::string update_str{"UPDATE Account SET "};
    std::string output_str{" OUTPUT "};

    if (fields_set & PpeSet)
    {
        update_str += "IsPPE = " + std::to_string(ppe);
        output_str += "inserted.IsPPE ";
    }

    if (fields_set & StateSet)
    {
        if (state >= Onboarded) // only update state past onboarding
        {
            update_str += "State = " + std::to_string(state);
            output_str += "inserted.State";

            if (fields_set & PpeSet)
            {
                update_str += ", ";
                output_str += ", ";
            }

            const int date_flags[]{Received,
                        Transmited,
                        Expertized,
                        Decided,
                        Notarized,
                        Paid};

            const char* date_strings[]{"ReceivedDate",
                                       "TransmitedDate",
                                       "ExpertizedDate",
                                       "DecidedDate",
                                       "NotarizedDate",
                                       "PaidDate"};

            auto result{nanodbc::execute(server::server::get().connection, select(usr))};
            if (!result.next()) return {};

            const auto date{trantor::Date::date().toFormattedStringLocal(false)};

            for (int i = 0; i <= 5; i++)
            {
                if (state & date_flags[i])
                {
                    if (result.is_null(date_strings[i]))
                    {
                        update_str += " , ";
                        update_str += date_strings[i];
                        update_str += " = '";
                        update_str += date;
                        update_str += '\'';

                        output_str += " , inserted.";
                        output_str += date_strings[i];
                    }
                }
                else
                {
                    if (!result.is_null(date_strings[i]))
                    {
                        update_str += " , ";
                        update_str += date_strings[i];
                        update_str += " = NULL";
                    }
                }
            }
        }
        else
            return {};
    }

    return update_str + output_str + " WHERE Id = " + std::to_string(id);
}

const std::string s_account::remove(const People::s_user& usr) const
{
    std::string str{"DELETE FROM Account WHERE Id = "
                    + std::to_string(id)};

    condition(str, usr, this); // workarount to condition without foreign object

    return str;
}

void s_account::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    if (!acnt) return;

    const auto date{trantor::Date::date().toDbStringLocal()};

    query.insert(0,
                 " UPDATE Account "
                 "SET UpdateDate = '"
                 + date +
                 "' ");

    query.append(" WHERE Id = " + std::to_string(acnt->id));
}

void s_account::condition(std::string& query,
                          const People::s_user& usr,
                          const s_account* acnt)
{
    if (!acnt) return;

    query.insert(0,
                 "SET NOCOUNT ON "
                 "IF EXISTS "
                 "(SELECT "
                 "a.Id "
                 "FROM Account a, "
                 "[User] u, "
                 "Company c "
                 "WHERE a.Id = "
                 + std::to_string(acnt->id) +
                 " AND u.id = a.AdvisorId "
                 "AND c.id = u.CompanyId "
                 + server::utils::clearance_close(usr) +
                 ") BEGIN ");

    query.append(" END ");
}

void s_account::update_reply(nanodbc::result& res,
                             Value& json_resp,
                             const s_account*)
{
    res.next();

    try
    {
        if (!res.is_null("State"))
            json_resp["accountState"] = states(res.get<int>("State"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("IsPPE"))
            json_resp["isPPE"] = (bool)res.get<int>("IsPPE");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ReceivedDate"))
            json_resp["receivedDate"] = server::utils::from_db_date_time(res.get<std::string>("ReceivedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("TransmitedDate"))
            json_resp["transmitedDate"] = server::utils::from_db_date_time(res.get<std::string>("TransmitedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ExpertizedDate"))
            json_resp["expertizedDate"] = server::utils::from_db_date_time(res.get<std::string>("ExpertizedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("DecidedDate"))
            json_resp["decidedDate"] = server::utils::from_db_date_time(res.get<std::string>("DecidedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("NotarizedDate"))
            json_resp["notarizedDate"] = server::utils::from_db_date_time(res.get<std::string>("NotarizedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("PaidDate"))
            json_resp["paidDate"] = server::utils::from_db_date_time(res.get<std::string>("PaidDate"));
    }
    catch (...) {}
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
        if (!res.is_null("IsPPE"))
            ppe = res.get<int>("IsPPE");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ReceivedDate"))
            receivedDate = server::utils::from_db_date_time(res.get<std::string>("ReceivedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("TransmitedDate"))
            transmitedDate = server::utils::from_db_date_time(res.get<std::string>("TransmitedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("ExpertizedDate"))
            expertizedDate = server::utils::from_db_date_time(res.get<std::string>("ExpertizedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("DecidedDate"))
            decidedDate = server::utils::from_db_date_time(res.get<std::string>("DecidedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("NotarizedDate"))
            notarizedDate = server::utils::from_db_date_time(res.get<std::string>("NotarizedDate"));
    }
    catch (...) {}

    try
    {
        if (!res.is_null("PaidDate"))
            paidDate = server::utils::from_db_date_time(res.get<std::string>("PaidDate"));
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
