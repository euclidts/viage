#ifndef C_COMPANY_HPP
#define C_COMPANY_HPP

#include "qnamespace.h"
#include <Item/company_item.hpp>

namespace Data
{

template <typename T>
struct item_list;

struct team_item;

struct c_company : public company_item
{
    c_company();

    static const constexpr auto qmlName{"Company"};
    static const constexpr auto uri{"Data"};

    enum roles
    {
        IdRole = Qt::UserRole,
        NameRole,
        TeamsRole
    };

    static QHash<int , QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    bool update(item_list<team_item>* ti);
    QJsonArray get(item_list<team_item>* ti) const;
};

}

#endif // COMPANY_ITEM_HPP
