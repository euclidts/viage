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
        if (!res.is_null("Street"))
            address->street = res.get<std::string>("Street");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Zip"))
            address->zip = res.get<int>("Zip");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("Canton"))
            address->canton = res.get<std::string>("Canton");
    }
    catch (nanodbc::index_range_error) {}

    try
    {
        if (!res.is_null("City"))
            address->city = res.get<std::string>("City");
    }
    catch (nanodbc::index_range_error) {}
}

const std::string s_address::fields() const
{
  return "Street = '"
          + address->street +
          "', Zip = '"
          + std::to_string(address->zip) +
          "', Canton = '"
          + address->canton +
          "', City = '"
          + address->city +
          "'";
}

}
}
