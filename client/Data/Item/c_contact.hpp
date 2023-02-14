#ifndef C_CONTACT_HPP
#define C_CONTACT_HPP

#include "qnamespace.h"
#include "c_infant.hpp"
#include <Item/contact_item.hpp>
#include <item_list.hpp>

namespace Data
{
namespace People
{
struct c_contact final : public contact_item
        , public c_infant<contact_item>
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

template<>
inline bool item_list<People::c_contact>::is_completed() const
{
    return is_empty_completed();
};

}
#endif // C_CONTACT_H
