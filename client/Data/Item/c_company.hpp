#ifndef C_COMPANY_HPP
#define C_COMPANY_HPP

#include "qnamespace.h"
#include <Item/company_item.hpp>
#include "c_base_item.hpp"

namespace Data
{

template <typename T>
struct item_list;

struct team_item;

struct c_company : public company_item
                 , public c_base_item
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

    void read(const Json::Value & json) { company_item::read(json); };
    void write(Json::Value & json) const { company_item::write(json); };

    bool is_completed() const { return company_item::is_completed(); };
};

}

#endif // COMPANY_ITEM_HPP
