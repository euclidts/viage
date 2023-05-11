#include "s_user.hpp"

namespace Data
{
namespace People
{
const std::vector<drogon_model::MetaData> metaData_{[]()
{
    std::vector<drogon_model::MetaData> meta{
        {"Login","std::string","varchar(24)",24,0,0,0},
        {"Password","std::string","varchar(32)",32,0,0,0},
        {"Clearance","int8_t","tinyint(4)",1,0,0,0},
        {"Beneficiary","std::string","varchar(37)",37,0,0,0},
        {"Bic","std::string","varchar(38)",38,0,0,0},
        {"Iban","std::string","varchar(42)",42,0,0,0},
        {"CompanyId","int8_t","tinyint(4)",1,0,0,0},
        {"TeamId","int8_t","tinyint(4)",1,0,0,0},
        {"IsLocked","int8_t","tinyint(4)",1,0,0,0}
    };

    for (const auto& data : s_person<s_user>::metaData_)
        meta.emplace_back(data);

    for (const auto& data : Places::s_address::metaData_)
        meta.emplace_back(data);

    return meta;
}()};

const std::string& s_user::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}

s_user::s_user()
    : user_item{}
    , s_person{}
    , sa{address}
    , last_access{trantor::Date::date()}
{
}

const std::string s_user::insert(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "INSERT INTO User "
           "(FirstName, LastName) "
           "OUTPUT Inserted.Id "
           "VALUES ('"
            + user_item::firstName +
            "', '"
            + user_item::lastName +
            "') ";
}

const std::string s_user::select(const s_user& usr) const
{
    if (usr.clearance < Administrator)
        return "";

    return search(usr) + " WHERE Id = " + std::to_string(id);
}

const std::string s_user::update(const People::s_user& usr) const
{
    if (usr.clearance < People::s_user::Administrator)
        return {};

    return "UPDATE User SET "
            + fields() +
            " WHERE Id = "
            + std::to_string(id);
}

void s_user::set(const Row &row)
{
    s_person::set(row);

    try
    {
        if (!row["Company"].isNull())
            company = row["Company"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["Clearance"].isNull())
            clearance = clearances(row["Clearance"].as<int>());
    }
    catch (...) {}

    try
    {
        if (!row["Team"].isNull())
            team = row["Team"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["Beneficiary"].isNull())
            beneficiary = row["Beneficiary"].as<std::string>();
    }
    catch (...) {}

    sa.set(row);

    try
    {
        if (!row["Iban"].isNull())
            iban = row["Iban"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["Bic"].isNull())
            bic = row["Bic"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["CompanyId"].isNull())
            company_id = row["CompanyId"].as<int>();
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
        if (!row["TeamId"].isNull())
            team_id = row["TeamId"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Caption"].isNull())
            team = row["Caption"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["IsLocked"].isNull())
            isLocked = row["IsLocked"].as<bool>();
    }
    catch (...) {}
}

const std::string s_user::fields() const
{
    return sa.fields() +
            ", "
            + s_person::fields() +
            ", CompanyId = "
            + std::to_string(company_id) +
            ", TeamId = "
            + std::to_string(team_id) +
            ", Beneficiary = '"
            + beneficiary +
            "', Iban = '"
            + iban +
            "', Bic = '"
            + bic +
            "'";
}

}
}
