#ifndef S_COMPANY_HPP
#define S_COMPANY_HPP

#include <s_user.hpp>
#include <nanodbc/nanodbc.h>
#include <Item/company_item.hpp>

namespace Data
{
struct s_company final : public company_item
{
    explicit s_company();

    static const constexpr auto table{"Company"};

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { company_item::read(json); }

    const std::string insert(const People::s_user& usr) const;
    const std::string update(const People::s_user& usr) const;

    template <typename T = std::nullptr_t>
    static const constexpr auto select(const People::s_user& usr, T* = nullptr)
    {
        if (usr.clearance < People::s_user::Administrator)
            return "";

        return "SELECT * "
               "FROM Company ";
    }
};

}

#endif // S_COMPANY_HPP
