#ifndef S_COMPANY_HPP
#define S_COMPANY_HPP

#include <nanodbc/nanodbc.h>
#include <Item/company_item.hpp>

namespace Data
{

struct s_company : public company_item
{
    explicit s_company();

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { company_item::read(json); }

    const std::string insert() const;
    static const constexpr auto select()
    {
        return "SELECT * "
               "FROM Company ";
    }

    const std::string update() const;

};

}

#endif // S_COMPANY_HPP
