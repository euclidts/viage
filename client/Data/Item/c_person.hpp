#ifndef C_PERSON_HPP
#define C_PERSON_HPP

#include <Item/person_item.hpp>
#include "c_base_item.hpp"

namespace Data
{
namespace People
{
struct c_person : virtual public person_item
                , protected c_base_item
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
