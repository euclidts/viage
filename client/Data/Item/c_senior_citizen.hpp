#ifndef C_SENIOR_CITIZEN_HPP
#define C_SENIOR_CITIZEN_HPP

#include "qnamespace.h"
#include <Item/senior_citizen_item.hpp>

namespace Data
{
namespace People
{

#define AGE_MIN 70
#define AGE_MAX 120

struct c_senior_citizen : public senior_citizen_item
{
    c_senior_citizen();

    static const constexpr auto uri{"People"};

    enum roles
    {
        BirthDayRole = Qt::UserRole,
        SexRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    bool is_completed() const { return senior_citizen_item::is_completed(); };
};

}
}

#endif // SENIOR_CITIZEN_ITEM_HPP
