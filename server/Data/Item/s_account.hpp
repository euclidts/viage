#ifndef S_ACOUNT_HPP
#define S_ACOUNT_HPP

#include <nanodbc/nanodbc.h>
#include "s_user.hpp"
#include <server_utils.hpp>
#include <Item/account_item.hpp>

namespace Data
{
struct s_account final : public account_item
{
    s_account();

    static const constexpr auto table{"Account"};

    void read(nanodbc::result& res);
    void read(const Json::Value& json) { account_item::read(json); }

    const std::string insert(const People::s_user &usr) const;
    const std::string update(const People::s_user &usr) const;

    static const constexpr basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr)
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
               "Company c "
               "WHERE b.OwnerAccountId = a.Id "
               "AND b.OwnerType = 'Owner' "
               "AND u.id = a.AdvisorId "
               "AND c.id = u.CompanyId "
                + server::utils::clearance_close(usr);
    };

//private:
//    void remove_multiple(nanodbc::result& res);
};

}

#endif // S_ACCOUNT_HPP
