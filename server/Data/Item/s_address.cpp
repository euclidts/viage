#include "s_address.hpp"
#include <Item/address_item.hpp>

namespace Data
{
namespace Places
{
s_address::s_address(address_item* ai)
    : address{ai}
{
}

void s_address::read(const nanodbc::result &res)
{
    try
    {
        if (!res.is_null("street"))
            address->street = res.get<std::string>("street");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("zip"))
            address->street = res.get<int>("zip");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("canton"))
            address->street = res.get<std::string>("canton");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("city"))
            address->street = res.get<std::string>("city");
    }
    catch (nanodbc::index_range_error) {}
}

}
}
