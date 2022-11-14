#ifndef C_TEAM_HPP
#define C_TEAM_HPP

#include <Item/team_item.hpp>
#include "c_base_item.hpp"

namespace Data
{
struct c_team : public team_item
              , protected c_base_item
{
    c_team();

    static const constexpr auto qmlName{"Team"};
    static const constexpr auto uri{"Data"};

    enum roles
    {
        IdRole = Qt::UserRole,
        CaptionRole,
        HasUsersRole
    };

    static QHash<int , QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);
};

}

#endif // C_TEAM_HPP
