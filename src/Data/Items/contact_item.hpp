#ifndef CONTACT_ITEM_H
#define CONTACT_ITEM_H

#include <QJsonObject>

#include "infant_item.hpp"

namespace Data
{
namespace People
{
struct contact_item : public infant_item
{   
    contact_item();

    const constexpr char* key() { return "contact"; };
    static const constexpr auto qmlName{"Contact"};

    bool isInfant{false};

    enum roles
    {
        // following infant_items roles
        IsInfantRole = Qt::UserRole + 5
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

#endif // CONTACT_ITEM_H
