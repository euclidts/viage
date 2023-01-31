#ifndef S_OWNER_HPP
#define S_OWNER_HPP

#include "s_infant.hpp"
#include <server_utils.hpp>
#include <Item/owner_item.hpp>

namespace Data
{
struct s_account;

template <typename T>
struct s_list;

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
                               s_list<s_owner>* list,
                               s_account* acnt);

    static void condition(std::string& query,
                          const People::s_user& usr,
                          s_account* acnt);;

    static const constexpr std::basic_string<char, std::char_traits<char>> select(
            const People::s_user& usr, s_account* acnt);

private:
    Places::s_address ads;
};

}
}

#endif // S_CONTACT_HPP
