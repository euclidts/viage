#ifndef S_CONTACT_HPP
#define S_CONTACT_HPP

#include "s_account.hpp"
#include "s_infant.hpp"
#include <server_utils.hpp>
#include <Item/contact_item.hpp>

namespace Data
{
struct s_account;

template <typename T>
struct s_list;

namespace People
{
struct s_contact final : public contact_item
                       , public s_infant<contact_item>
{
    s_contact();

    void set(const nanodbc::result& res);

    const std::string insert(const s_user& usr, s_account* acnt = nullptr) const;
    const std::string update(const s_user& usr, s_account* acnt = nullptr) const;

    static void foreign_update(std::string& query,
                               s_list<s_contact>* list,
                               s_account* acnt = nullptr);

    static void condition(std::string& query,
                          const s_user& usr,
                          s_account* acnt);

    static const constexpr std::basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr,
            s_account* acnt = nullptr)
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
    }
};

}
}

#endif // S_CONTACT_HPP
