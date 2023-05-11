#include "s_address.hpp"
#include <Item/address_item.hpp>
#include <drogon/orm/Field.h>

namespace Data
{
namespace Places
{
const std::vector<drogon_model::MetaData> s_address::metaData_={
    {"Street","std::string","varchar(36)",36,0,0,0},
    {"City","std::string","varchar(10)",10,0,0,0},
    {"Canton","std::string","varchar(10)",10,0,0,0},
    {"Zip","int32_t","mediumint(9)",3,0,0,0}
};
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
