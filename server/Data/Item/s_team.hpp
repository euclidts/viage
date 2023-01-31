#ifndef S_TEAM_HPP
#define S_TEAM_HPP

#include "s_user.hpp"
#include "s_company.hpp"
#include <nanodbc/nanodbc.h>
#include <Item/team_item.hpp>

namespace Data
{
struct s_team final : public team_item
{
    explicit s_team();

    static const constexpr auto table{"Team"};

    int companyId{0};

    void set(const nanodbc::result& res);
    void read(const Json::Value& json);

    const std::string insert(const People::s_user& usr,
                             s_company* foreign = nullptr) const;
    const std::string update(const People::s_user& usr,
                             s_company* foreign = nullptr) const;

    static void condition(std::string& query,
                          const People::s_user& usr,
                          s_company* foreign = nullptr) {};

    static const constexpr std::basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr,
            s_company* foreign = nullptr)
    {
        if (usr.clearance < People::s_user::Administrator && !foreign)
            return "";

        return "SELECT * FROM Team "
               "WHERE "
                + std::string{foreign->foreign_key}
        + " = "
        + std::to_string(foreign->id);
    }
};

}

#endif // S_COMPANY_HPP
