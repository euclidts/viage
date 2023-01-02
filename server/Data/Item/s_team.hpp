#ifndef S_TEAM_HPP
#define S_TEAM_HPP

#include <s_user.hpp>
#include <nanodbc/nanodbc.h>
#include <Item/team_item.hpp>

namespace Data
{
struct s_team : public team_item
{
    explicit s_team();

    static const constexpr auto table{"Team"};

    int companyId{0};

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { team_item::read(json); }

    const std::string insert(const People::s_user& usr) const;

    template <typename T = std::nullptr_t>
    static const constexpr std::basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr,
            T* foreign = nullptr)
    {
        if (usr.clearance < People::s_user::Administrator && !foreign)
            return "";

        return "SELECT * FROM Team "
               "WHERE "
                + std::string{T::foreign_key} +
        " = "
        + std::to_string(foreign->id);
    }

    const std::string update(const People::s_user& usr) const;
};

}

#endif // S_COMPANY_HPP
