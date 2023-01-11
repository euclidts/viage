#ifndef C_OWNER_HPP
#define C_OWNER_HPP

#include "qnamespace.h"
#include <Item/owner_item.hpp>
#include "c_infant.hpp"
#include "c_address.hpp"

namespace Data
{
namespace People
{
struct c_owner : public owner_item,
                 public c_infant<owner_item>
{
    c_owner();

    static const constexpr auto qmlName{"Owner"};

    enum roles
    {
        // following infant_items roles
        BirthDayRole = Qt::UserRole + 7,
        CivilStatusRole,
        AVSRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const Json::Value& json) { owner_item::read(json); }
    void write(Json::Value& json) const { owner_item::write(json); }

    bool is_completed() const { return owner_item::is_completed(); };

protected:
    Places::c_address ca;
};

}
}

#endif // C_OWNER_HPP
