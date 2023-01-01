#ifndef S_ACOUNT_HPP
#define S_ACOUNT_HPP

#include "s_user.hpp"
#include <nanodbc/nanodbc.h>
#include <Item/account_item.hpp>

namespace Data
{
struct s_account : public account_item
{
    s_account();

    static const constexpr auto table{"Account"};

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { account_item::read(json); }

    const std::string fields() const;
    const std::string insert() const;
    const std::string update() const;

    static const constexpr auto select()
    {
        return "SELECT "
               "a.Id, "
               "Acronym, "
               "CreationDate, "
               "UpdateDate, "
               "State, "
               "a.Street, "
               "a.City, "
               "a.Canton, "
               "a.Zip, "
               "b.FirstName, "
               "b.LastName, "
               "u.FirstName AS AdvisorFirstName, "
               "u.LastName AS AdvisorLastName, "
               "c.Name "
               "FROM Account a, "
               "BaseOwner b, "
               "[User] u, "
               "Company c, "
               "Team t "
               "WHERE b.OwnerAccountId = a.Id "
               "AND b.OwnerType = 'Owner' "
               "AND u.id = a.AdvisorId "
               "AND c.id = u.CompanyId ";
    };

    static const constexpr auto select(const People::s_user& usr)
    {
        std::string str{};

        switch (usr.clearance)
        {
        case People::s_user::Vendor:
            str = "AND a.AdvisorId = " + std::to_string(usr.id);
            break;
        case People::s_user::Manager:
            str = "AND u.TeamId = " + std::to_string(usr.team_id);
            break;
        case People::s_user::Director:
            str = "AND u.CompanyId = " + std::to_string(usr.company_id);
            break;
        case People::s_user::None:
            return str;
        default:
            break;
        }

        return std::string{select()} + str;
    };
};

}

#endif // S_ACCOUNT_HPP
