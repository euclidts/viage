#ifndef S_USER_HPP
#define S_USER_HPP

#include "s_person.hpp"
#include "s_address.hpp"
#include <Item/user_item.hpp>
#include <trantor/utils/Date.h>

namespace Data
{
namespace People
{
struct s_user final : public user_item
                    , public s_person<user_item>
{
    s_user();

    static const constexpr auto table{"User"};

    trantor::Date last_access;

    void set(const nanodbc::result& res);

    const std::string fields() const;
    const std::string insert(const s_user& usr) const;
    const std::string update(const s_user& usr) const;

    static void foreign_update(std::string& query, bool complete) {};
    static void condition(std::string& query, const s_user& usr) {};
    static void update_reply(nanodbc::result& res, Json::Value& json) {};

    static const constexpr std::string select(const s_user& usr)
    {
        if (usr.clearance < Administrator)
            return "";

        return "SELECT "
               "a.[Id], "
               "FirstName, "
               "LastName, "
               "Login, "
               "EMail, "
               "Phone, "
               "Clearance, "
               "Beneficiary, "
               "Bic, "
               "Iban, "
               "Street, "
               "City, "
               "Canton, "
               "Zip, "
               "a.[CompanyId], "
               "TeamId, "
               "IsLocked, "
               "b.[Name], "
               "c.[Caption] "
               "FROM (([User] a "
               "LEFT JOIN Company b "
               "ON a.[CompanyId] = b.[Id]) "
               "LEFT JOIN Team c "
               "ON a.[TeamId] = c.[Id]) ";
    };

protected:
    Places::s_address sa;
};

}
}

#endif // S_USER_HPP
