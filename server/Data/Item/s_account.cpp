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
    const auto date{trantor::Date::date().toFormattedStringLocal(false)};

    return "INSERT INTO Account "
           "(CreationDate, UpdateDate, AdvisorId, State, HabitatType) "
           "VALUES ('"
            + date +
            "', '"
            + date +
            "', "
            + std::to_string(usr.id) +
           ", 0, 0) "
            "RETURNING Id ";
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

const std::string s_account::update(const People::s_user& usr, const s_account* acnt) const
{
    if (fields_set == None) return {};

    std::string update_str{"UPDATE Account SET "};

    if (fields_set & PpeSet)
        update_str += "IsPPE = " + std::to_string(ppe);

    if (fields_set & StateSet)
    {
        if (state >= Onboarded) // only update state past onboarding
        {
            update_str += "State = " + std::to_string(state);

            if (fields_set & PpeSet)
                update_str += ", ";

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

            auto result{server::server::get().execute(select(usr))};
            if (result.empty()) return{};

            const auto date{trantor::Date::date().toFormattedStringLocal(false)};

            for (int i = 0; i <= 5; i++)
            {
                if (state & date_flags[i])
                {
                    if (result.front()[date_strings[i]].isNull())
                    {
                        update_str += " , ";
                        update_str += date_strings[i];
                        update_str += " = '";
                        update_str += date;
                        update_str += '\'';
                    }
                }
                else
                {
                    if (!result.front()[date_strings[i]].isNull())
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

    return update_str + " WHERE Id = " + std::to_string(id);
}

const std::string s_account::remove(const People::s_user& usr) const
{
    return "DELETE FROM Account WHERE Id = " + std::to_string(id);
}

void s_account::foreign_update(std::string& query, bool complete, const s_account* acnt)
{
    if (!acnt) return;

    const auto date{trantor::Date::date().toFormattedStringLocal(false)};

    if (!query.empty()) query.insert(0, ", ");

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
                 "IF EXISTS "
                 "(SELECT "
                 "a.Id "
                 "FROM Account a, "
                 "User u, "
                 "Company c "
                 "WHERE a.Id = "
                 + std::to_string(acnt->id) +
                 " AND u.id = a.AdvisorId "
                 "AND c.id = u.CompanyId "
                 + server::utils::clearance_close(usr) +
                 ") BEGIN ");

    query.append(" END ");
}

void s_account::select_updated(std::string& query, const s_account* acnt)
{
    if (!acnt) return;
    if (!query.empty()) query.insert(0, ", ");
    query.insert(0, "SELECT a.UpdateDate");

    if (acnt->fields_set != None)
    {
        std::string output_str{};

        if (acnt->fields_set & PpeSet)
            output_str += ", a.IsPPE";

        if (acnt->fields_set & StateSet)
        {
            if (!query.find("a.State"))
                output_str += ", a.State";

            if (acnt->state >= Onboarded) // only update state past onboarding
                output_str += ", a.ReceivedDate"
                              ", a.TransmitedDate"
                              ", a.ExpertizedDate"
                              ", a.DecidedDate"
                              ", a.NotarizedDate"
                              ", a.PaidDate";
        }

        query.append(output_str);
    }

    query.append(" FROM Account a WHERE Id = " + std::to_string(acnt->id));
}

void s_account::update_reply(const Result& res,
                             Value& json_resp,
                             const s_account*)
{
    const auto row{res.front()};

    try
    {
        if (!row["State"].isNull())
            json_resp["accountState"] = states(row["State"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["IsPPE"].isNull())
            json_resp["isPPE"] = (bool)row["IsPPE"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["ReceivedDate"].isNull())
            json_resp["receivedDate"] = row["ReceivedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["TransmitedDate"].isNull())
            json_resp["transmitedDate"] = row["TransmitedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["ExpertizedDate"].isNull())
            json_resp["expertizedDate"] = row["ExpertizedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["DecidedDate"].isNull())
            json_resp["decidedDate"] = row["DecidedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["NotarizedDate"].isNull())
            json_resp["notarizedDate"] = row["NotarizedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["PaidDate"].isNull())
            json_resp["paidDate"] = row["PaidDate"].as<std::string>();
    }
    catch (...) {}
}

void s_account::set(const Row& row)
{
    try
    {
        if (!row["Id"].isNull())
            id = row["Id"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Acronym"].isNull())
            acronym = row["Acronym"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["CreationDate"].isNull())
            created = row["CreationDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["UpdateDate"].isNull())
            modified = row["UpdateDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["State"].isNull())
            state = states(row["State"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["Name"].isNull())
            company = row["Name"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["AdvisorFirstName"].isNull())
            advisorFirstName = row["AdvisorFirstName"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["AdvisorLastName"].isNull())
            advisorLastName = row["AdvisorLastName"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["IsPPE"].isNull())
            ppe = row["IsPPE"].as<bool>();
    }
    catch (...) {}

    try
    {
        if (!row["ReceivedDate"].isNull())
            receivedDate = row["ReceivedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["TransmitedDate"].isNull())
            transmitedDate = row["TransmitedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["ExpertizedDate"].isNull())
            expertizedDate = row["ExpertizedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["DecidedDate"].isNull())
            decidedDate = row["DecidedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["NotarizedDate"].isNull())
            notarizedDate = row["NotarizedDate"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["PaidDate"].isNull())
            paidDate = row["PaidDate"].as<std::string>();
    }
    catch (...) {}
}
}
