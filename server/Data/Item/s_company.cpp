#include "s_company.hpp"

namespace Data
{
s_comapny::s_comapny()
{
}

void s_comapny::read(const nanodbc::result &res)
{
    try
    {
        if (!res.is_null("Id"))
            id = res.get<int>("Id");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Name"))
            name = res.get<std::string>("Name");
    }
    catch (nanodbc::index_range_error) {}
}

}
