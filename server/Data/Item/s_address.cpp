#include "s_address.hpp"
#include <Item/address_item.hpp>
#include <drogon/orm/Field.h>

namespace Data
{
namespace Places
{
s_address::s_address(address_item* ai)
    : address{ai}
{
}

void s_address::set(const Row& row)
{
    try
    {
        if (!row["Street"].isNull())
            address->street = row["Street"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["Zip"].isNull())
            address->zip = row["Zip"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["Canton"].isNull())
            address->canton = row["Canton"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["City"].isNull())
            address->city = row["City"].as<std::string>();
    }
    catch (...) {}
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
