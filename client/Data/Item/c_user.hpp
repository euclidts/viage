#ifndef C_USER_HPP
#define C_USER_HPP

#include "qnamespace.h"
#include "c_person.hpp"
#include "c_address.hpp"
#include <Item/user_item.hpp>

namespace Data
{
namespace People
{
struct c_user : public user_item
              , public c_person
{
    c_user();

    static const constexpr auto qmlName{"User"};

    enum roles
    {
        // following c_person roles
        CompanyRole = Qt::UserRole + 5,
        ClearanceRole,
        TeamNameRole,
        BeneficiaryRole,
        // gap left for c_address roles
        IbanRole = Qt::UserRole + 14,
        BicRole,
        CompanyIdRole,
        TeamIdRole,
        LockedRole,
        CompletedRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const Json::Value& json) { user_item::read(json); }
    void write(Json::Value& json) const { user_item::write(json); }

    bool is_completed() const { return user_item::is_completed(); }

protected:
    Places::c_address ca;
};

}
}

#endif // C_USER_HPP
