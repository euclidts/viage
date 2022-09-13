#ifndef INFANT_ITEM_HPP
#define INFANT_ITEM_HPP

#include <QJsonObject>

#include "person_item.hpp"
#include "senior_citizen_item.hpp" // needed for sexes enum

namespace Data
{
namespace People
{
struct infant_item : public person_item
{   
    infant_item();

    senior_citizen_item::sexes sex{senior_citizen_item::M};

    enum roles
    {
        // following infant_item roles
        SexRole = Qt::UserRole + 6
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject &json) const;

    bool is_completed() const;
};

}
}

#endif // INFANT_ITEM_HPP
