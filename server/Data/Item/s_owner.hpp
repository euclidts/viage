#ifndef S_OWNER_HPP
#define S_OWNER_HPP

#include "s_account.hpp"
#include "s_infant.hpp"
#include <server_utils.hpp>
#include <Item/owner_item.hpp>

namespace Data
{
struct s_account;

namespace People
{
struct s_owner final : public owner_item
                     , public s_infant<owner_item>
{
    s_owner();

    void set(const nanodbc::result& res);

    const std::string insert(const s_user& usr, s_account* acnt) const;
    const std::string update(const s_user& usr, s_account* acnt) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               s_account* acnt);

    static void condition(std::string& query,
                          const s_user& usr,
                          s_account* acnt);;

    static const constexpr std::string select(const s_user& usr,
                                              s_account* acnt)
    {
        return "SELECT "
               "DISTINCT(b.Id), "
               "b.FirstName, "
               "b.LastName, "
               "b.Sex, "
               "b.Phone, "
               "b.EMail, "
               "b.IsInfant "
               "FROM Account a, "
               "BaseOwner b, "
               "[User] u "
               "WHERE b.OwnerAccountId = "
                + std::to_string(acnt->id) +
                " AND b.OwnerType = 'Owner' "
                + server::utils::clearance_close(usr);
    }

private:
    Places::s_address ads;
};

}
}

#endif // S_CONTACT_HPP
