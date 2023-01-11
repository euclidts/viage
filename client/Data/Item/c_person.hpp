#ifndef C_PERSON_HPP
#define C_PERSON_HPP

#include "qnamespace.h"
#include <Item/person_item.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct c_person : virtual public person_item<T>
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

#include "c_person.cpp"
#endif // C_PERSON_HPP
