#include "s_person.hpp"

namespace Data
{
namespace People
{
s_person::s_person()
    : person_item{}
{
}

void s_person::read(const nanodbc::result& res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("FirstName"))
            firstName = res.get<std::string>("FirstName");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("LastName"))
            lastName = res.get<std::string>("LastName");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Phone"))
            phone = res.get<std::string>("Phone");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("EMail"))
            eMail = res.get<std::string>("EMail");
    }
    catch (nanodbc::index_range_error) {}
}

}
}
