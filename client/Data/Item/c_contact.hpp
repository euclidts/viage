#ifndef C_CONTACT_H
#define C_CONTACT_H

#include "qnamespace.h"
#include "c_infant.hpp"
#include <Item/contact_item.hpp>

namespace Data
{
namespace People
{
struct c_contact : public contact_item
                 , public c_infant
{   
    c_contact();

    static const constexpr auto qmlName{"Contact"};

    enum roles
    {
        // following infant_items roles
        IsInfantRole = Qt::UserRole + 5
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const Json::Value& json) { contact_item::read(json); }
    void write(Json::Value& json) const { contact_item::write(json); }

    bool is_completed() const { return contact_item::is_completed(); };
};

}
}

#endif // C_CONTACT_H