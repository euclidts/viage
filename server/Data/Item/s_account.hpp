#ifndef S_ACOUNT_HPP
#define S_ACOUNT_HPP

#include <s_base_data.hpp>
#include <server_utils.hpp>
#include <Item/account_item.hpp>

namespace Data
{
struct s_account final : public account_item
//                       , public s_base_data<account_item>
{
    s_account();
    void read(const Value& json);

    static const constexpr auto table{"Account"};

    void set(const Row& row);
    void set(const Result& res)
    {
        if (!res.empty()) set(res.front());
    };

    const std::string insert(const People::s_user& usr) const;
    const std::string select(const People::s_user& usr) const;
    const std::string update(const People::s_user& usr) const;
    const std::string remove(const People::s_user& usr) const;

    static void foreign_update(std::string& query,
                               bool complete,
                               const s_account* acnt = nullptr);

    static void condition(std::string& query,
                          const People::s_user& usr,
                          const s_account* acnt = nullptr);

    static void update_reply(const Result& res,
                             Value& json_resp,
                             const s_account* = nullptr);

    static const constexpr std::basic_string<char, std::char_traits<char>> search(
            const People::s_user& usr)
    {
        return "SELECT "
               "a.Id, "
               "Acronym, "
               "CreationDate, "
               "UpdateDate, "
               "State, "
               "IsPPE, "
               "a.Street, "
               "a.City, "
               "a.Canton, "
               "a.Zip, "
               "o.FirstName, "
               "o.LastName, "
               "u.FirstName AS AdvisorFirstName, "
               "u.LastName AS AdvisorLastName, "
               "c.Name "
               "FROM Account a, "
               "Owner o, "
               "User u, "
               "Company c "
               "WHERE o.AccountId = a.Id "
               "AND u.id = a.AdvisorId "
               "AND c.id = u.CompanyId "
                + server::utils::clearance_close(usr);
    };

private:
    enum setableFields
    {
        None = 0,
        PpeSet = 1,
        StateSet = 2
    };

    int fields_set{None};
};

}

#endif // S_ACCOUNT_HPP
