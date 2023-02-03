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

    static void condition(std::string& query, const s_user& usr) {};

    static const constexpr std::string select(const s_user& usr);;

protected:
    Places::s_address sa;
};

}
}

#endif // S_USER_HPP
