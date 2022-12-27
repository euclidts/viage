#ifndef S_COMPANY_HPP
#define S_COMPANY_HPP

#include <nanodbc/nanodbc.h>
#include <Item/company_item.hpp>

namespace Data
{

struct s_comapny : public company_item
{
    explicit s_comapny();

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { company_item::read(json); }
    //    void write(nanodbc::result& res);

    static const constexpr auto select()
    {
        return "SELECT * "
               "FROM Company ";
    }
};

}

#endif // S_COMPANY_HPP
