#ifndef S_CONTACT_HPP
#define S_CONTACT_HPP

#include "s_infant.hpp"
#include "s_account.hpp"
#include <s_list.hpp>
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
    const std::string remove(const s_user& usr, s_account* acnt = nullptr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               s_account* acnt = nullptr);

    static void condition(std::string& query,
                          const s_user& usr,
                          s_account* acnt = nullptr);

    static void update_reply(nanodbc::result& res,
                             Json::Value& json,
                             s_account* acnt);

    static const constexpr std::string select(const s_user& usr,
                                              s_account* acnt)
    {
        return "SELECT DISTINCT "
               "b.Id, "
               "b.FirstName, "
               "b.LastName, "
               "b.Sex, "
               "b.Phone, "
               "b.EMail, "
               "b.IsInfant "
               "FROM Account a, "
               "BaseOwner b, "
               "[User] u "
               "WHERE b.InfantAccountId = "
                + std::to_string(acnt->id) +
                " AND b.OwnerType = 'Contact' "
                + server::utils::clearance_close(usr);
    }
};
}

template<>
inline bool item_list<People::s_contact>::is_completed() const
{
    return is_empty_completed();
};
}

#endif // S_CONTACT_HPP
