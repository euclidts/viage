#include "s_account.hpp"

namespace Data
{
s_account::s_account()
    : account_item{}
{
}

const std::string s_account::insert() const
{
    return {};
//    return "INSERT INTO [User] "
//           "(FirstName, LastName) "
//           "OUTPUT Inserted.Id "
//           "VALUES ('"
//            + firstName +
//            "', '"
//            + lastName +
//            "') ";
}

const std::string s_account::update() const
{
    return {};
//    return "UPDATE [User] SET "
//            + fields() +
//            " WHERE Id = "
    //            + std::to_string(id);
}

void s_account::read(nanodbc::result& res)
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
            created = res.get<std::string>("CreationDate");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("UpdateDate"))
            modified = res.get<std::string>("UpdateDate");
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

const std::string s_account::fields() const
{
    return {};
//    return sa.fields() +
//            ", "
//            + s_person::fields() +
//            ", CompanyId = "
//            + std::to_string(company_id) +
//            ", TeamId = "
//            + std::to_string(team_id) +
//            ", Beneficiary = '"
//            + beneficiary +
//            "', Iban = '"
//            + iban +
//            "', Bic = '"
//            + bic +
//            "'";
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
