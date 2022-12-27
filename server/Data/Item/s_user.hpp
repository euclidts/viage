#ifndef S_USER_HPP
#define S_USER_HPP

#include <nanodbc/nanodbc.h>
#include "s_person.hpp"
#include "s_address.hpp"
#include <Item/user_item.hpp>
#include <trantor/utils/Date.h>

namespace Data
{
namespace People
{
struct s_user : public user_item
        , public s_person
{
    s_user();

    trantor::Date last_access;

    void read(const nanodbc::result& res);
    void read(const Json::Value& json) { user_item::read(json); }
    //    void write(nanodbc::result& res);

    static const constexpr auto select()
    {
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
