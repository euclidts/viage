#ifndef S_OWNER_HPP
#define S_OWNER_HPP

#include "s_account.hpp"
#include "s_infant.hpp"
#include <server_utils.hpp>
#include <Item/owner_item.hpp>

namespace Data
{
namespace People
{
struct s_owner final : public owner_item
                     , public s_infant<owner_item>
{
    s_owner();

    void set(const nanodbc::result& res);

    const std::string insert(const s_user& usr, s_account* acnt = nullptr) const;
    const std::string update(const s_user& usr, s_account* acnt = nullptr) const;

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
               " AND b.OwnerType = 'Owner' "
                + server::utils::clearance_close(usr);
    };

    static void enclose_condition(string &query,
                           const People::s_user& usr,
                           s_account* acnt)
    {
        acnt->enclose_condition(query, usr, acnt);
    }

private:
    Places::s_address ads;
};

}
}

#endif // S_CONTACT_HPP
