#ifndef C_INFANT_HPP
#define C_INFANT_HPP

#include "qnamespace.h"
#include "c_person.hpp"
#include <Item/infant_item.hpp>

namespace Data
{
namespace People
{
struct c_infant : public virtual infant_item
                , public c_person
{   
    c_infant();

    enum roles
    {
        // following infant_item roles
        SexRole = Qt::UserRole + 6
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const Json::Value& json) { infant_item::read(json); }
    void write(Json::Value& json) const { infant_item::write(json); }

    bool is_completed() const { return infant_item::is_completed(); };
};

}
}

#endif // C_INFANT_HPP
