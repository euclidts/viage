#ifndef C_PERSON_HPP
#define C_PERSON_HPP

#include "qnamespace.h"
#include <Item/person_item.hpp>

namespace Data
{
namespace People
{
struct c_person : public person_item
{
    static const constexpr auto uri{"People"};

    enum roles
    {
        IdRole = Qt::UserRole,
        FirstNameRole,
        LastNameRole,
        PhoneRole,
        EmailRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

protected:
    c_person();
};

}
}

#endif // C_PERSON_HPP
