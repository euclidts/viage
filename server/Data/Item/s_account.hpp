#ifndef S_ACOUNT_HPP
#define S_ACOUNT_HPP

#include "s_user.hpp"
#include <nanodbc/nanodbc.h>
#include <Item/account_item.hpp>

namespace Data
{
struct s_account final : public account_item
{
    s_account();

    static const constexpr auto table{"Account"};

    void read(nanodbc::result& res);
    void read(const Json::Value& json) { account_item::read(json); }

    const std::string fields() const;
    const std::string insert(const People::s_user &usr) const;
    const std::string update(const People::s_user &usr) const;

    template <typename T = nullptr_t>
    static const constexpr basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr,
            T* = nullptr)
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
            return "";
        default:
            break;
        }

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
               "Company c "
               "WHERE b.OwnerAccountId = a.Id "
               "AND b.OwnerType = 'Owner' "
               "AND u.id = a.AdvisorId "
               "AND c.id = u.CompanyId "
                + str;
    };

//private:
//    void remove_multiple(nanodbc::result& res);
};

}

#endif // S_ACCOUNT_HPP
