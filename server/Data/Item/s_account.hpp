#ifndef S_ACOUNT_HPP
#define S_ACOUNT_HPP

#include <nanodbc/nanodbc.h>
#include <s_base_data.hpp>
#include <server_utils.hpp>
#include <Item/account_item.hpp>

namespace Data
{
struct s_account final : public account_item
//                       , public s_base_data<account_item>
{
    s_account();

    static const constexpr auto table{"Account"};

    void set(nanodbc::result& res);

    const std::string insert(const People::s_user& usr) const;
    const std::string update(const People::s_user& usr) const;

    static void foreign_update(string& query,
                               s_account* acnt = nullptr)
    {
        if (!acnt) return;

        const auto date{trantor::Date::date().toDbStringLocal()};

        query.insert(0,
                     "UPDATE Account "
                     "SET UpdateDate = '"
                     + date +
                     "' ");

        query.append("WHERE Id = " + std::to_string(acnt->id));
    };

    static void condition(std::string& query,
                          const People::s_user& usr,
                          s_account* acnt = nullptr)
    {
        query.insert(0,
                     "IF EXISTS "
                     "(SELECT "
                     "a.Id "
                     "FROM Account a, "
                     "[User] u, "
                     "Company c "
                     "WHERE a.Id = "
                     + std::to_string(acnt->id) +
                     "AND u.id = a.AdvisorId "
                     "AND c.id = u.CompanyId "
                     + server::utils::clearance_close(usr) +
                     ") BEGIN ");

        query.append(" END ");
    };

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

private:


    //    void remove_multiple(nanodbc::result& res);
};

}

#endif // S_ACCOUNT_HPP
