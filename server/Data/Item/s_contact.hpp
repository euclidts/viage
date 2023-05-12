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

    void set(const Row& row);
    void set(const Result& res) { s_base_data::set(res); };

    const std::string insert(const s_user& usr, const s_account* acnt = nullptr) const;
    const std::string select(const s_user& usr, const s_account* acnt = nullptr) const;
    const std::string update(const s_user& usr, const s_account* acnt = nullptr) const;
    const std::string remove(const s_user& usr, const s_account* acnt = nullptr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               const s_account* acnt = nullptr);

    static void condition(std::string& query,
                          const s_user& usr,
                          const s_account* acnt = nullptr);

    static void update_reply(const Result& res,
                             Json::Value& json,
                             const s_account* acnt);

    static const constexpr std::string search(const s_user& usr,
                                              const s_account* acnt)
    {
        return "SELECT DISTINCT "
               "c.Id, "
               "c.FirstName, "
               "c.LastName, "
               "c.Sex, "
               "c.Phone, "
               "c.EMail, "
               "c.IsInfant "
               "FROM Account a, "
               "Contact c, "
               "User u "
               "WHERE c.AccountId = "
                + std::to_string(acnt->id)
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
