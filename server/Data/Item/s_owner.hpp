#ifndef S_OWNER_HPP
#define S_OWNER_HPP

#include "s_account.hpp"
#include "s_infant.hpp"
#include "s_list.hpp"
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

    void set(const Row& row);
    void set(const Result& res) { s_base_data::set(res); };

    const std::string insert(const s_user& usr, const s_account* acnt) const;
    const std::string select(const s_user& usr, const s_account* acnt) const;
    const std::string update(const s_user& usr, const s_account* acnt) const;
    const std::string remove(const s_user& usr, const s_account* acnt = nullptr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               const s_account* acnt);

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
               "o.Id, "
               "o.FirstName, "
               "o.LastName, "
               "o.Sex, "
               "o.Phone, "
               "o.EMail, "
               "o.AVS, "
               "o.BirthDay, "
               "o.CivilStatus, "
               "o.CivilStatus, "
               "o.Street, "
               "o.City, "
               "o.Canton, "
               "o.Zip "
               "FROM Account a, "
               "Owner o, "
               "User u "
               "WHERE o.AccountId = "
                + std::to_string(acnt->id)
                + server::utils::clearance_close(usr);
    }

private:
    Places::s_address ads;
};
}

template<>
template<>
inline std::string s_list<People::s_owner>::update(const People::s_user& usr,
                                                   const s_account* acnt) const
{
    std::string str{};

    if (!m_items.empty())
    {
        for (const auto& item : m_items)
            str += item.update(usr, acnt);

        auto owner{m_items[0]};

        auto first{owner.firstName};
        auto last{owner.lastName};

        if (first.size() > 3)
            first.erase(first.begin() + 3, first.end());

        if (last.size() > 3)
            last.erase(last.begin() + 3, last.end());

        auto concat{last + first};
        std::transform(concat.begin(), concat.end(), concat.begin(),
                       [](unsigned char c) { return std::toupper(c); });

        auto year{owner.birthDay};

        if (year.size() > 3)
        {
            year.erase(year.begin(), year.end() - 2);
            concat += year;
        }

        str += "UPDATE Account "
               "SET Acronym = '"
                + concat +
                "' WHERE Id = "
                + std::to_string(acnt->id) +
                "; ";
    }

    return str;
}
}

#endif // S_CONTACT_HPP
