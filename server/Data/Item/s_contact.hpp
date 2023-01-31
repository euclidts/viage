#ifndef S_CONTACT_HPP
#define S_CONTACT_HPP

#include "s_account.hpp"
#include "s_infant.hpp"
#include "s_user.hpp"
#include <server_utils.hpp>
#include <Item/contact_item.hpp>

namespace Data
{
namespace People
{
struct s_contact final : public contact_item
        , public s_infant<contact_item>
{
    s_contact();

    void set(const nanodbc::result& res);

    const std::string insert(const s_user& usr, s_account* acnt = nullptr) const;
    const std::string update(const s_user& usr, s_account* acnt = nullptr) const;

    template <typename T>
    static void foreign_update(string& query,
                               const T& self,
                               s_account* acnt = nullptr)
    {
        const auto date{trantor::Date::date().toDbStringLocal()};

        query.append("UPDATE Account "
                     "SET UpdateDate = '"
                     + date +
                     "' ");

        if (self.is_completed() || self.empty())
            query.append(", State |= " + std::to_string(account_item::ContactsCompleted));

        query.append("WHERE Id = " + std::to_string(acnt->id));
    };

    static void condition(string &query,
                          const People::s_user& usr,
                          s_account* acnt)
    {
        acnt->condition(query, usr, acnt);
    };

    static const constexpr std::basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr, s_account* acnt = nullptr)
    {
        return "SELECT "
               "b.Id, "
               "b.FirstName, "
               "b.LastName, "
               "b.Sex, "
               "b.Phone, "
               "b.EMail, "
               "b.IsInfant, "
               "FROM Account a, "
               "BaseOwner b, "
               "[User] u "
               "WHERE b.InfantAccountId = "
                + std::to_string(acnt->id) +
                " AND b.OwnerType = 'Contact' "
                + server::utils::clearance_close(usr);
    };
};

}
}

#endif // S_CONTACT_HPP