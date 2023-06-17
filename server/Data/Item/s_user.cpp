#include "s_user.hpp"

namespace Data
{
namespace People
{
s_user::s_user()
    : user_item{}
    , s_person{}
    , sa{address}
{
}

const std::string s_user::insert(const People::s_user& usr) const
{
    if (usr.clearance < Administrator) return {};

    return "INSERT INTO User "
           "(FirstName, LastName) "
           "VALUES ('"
            + user_item::firstName +
            "', '"
            + user_item::lastName +
            "') RETURNING Id";
}

const std::string s_user::select(const s_user& usr) const
{
    if (usr.clearance < Administrator) return {};

    return search(usr) + " WHERE Id = " + std::to_string(id);
}

const std::string s_user::update(const People::s_user& usr) const
{
    if (usr.clearance < Administrator) return {};

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
