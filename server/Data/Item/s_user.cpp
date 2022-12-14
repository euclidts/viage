#include "s_user.hpp"

namespace Data
{
namespace People
{
s_user::s_user()
    : user_item{}
    , s_person{}
    , sa{&address}
{
}

void s_user::read(const nanodbc::result& res)
{
    try
    {
        if (!res.is_null("Company"))
            company = res.get<std::string>("Company");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Clearance"))
            clearance = clearances(res.get<int>("Clearance"));
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Team"))
            team = res.get<std::string>("Team");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Beneficiary"))
            beneficiary = res.get<std::string>("Beneficiary");
    }
    catch (nanodbc::index_range_error) {}

    sa.read(res);

    try
    {
        if (!res.is_null("Iban"))
            iban = res.get<std::string>("Iban");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Bic"))
            bic = res.get<std::string>("Bic");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("CompanyId"))
            company_id = res.get<int>("CompanyId");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("TeamId"))
            team_id = res.get<int>("TeamId");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("IsLocked"))
            isLocked = res.get<int>("IsLocked");
    }
    catch (nanodbc::index_range_error) {}
}

}
}
