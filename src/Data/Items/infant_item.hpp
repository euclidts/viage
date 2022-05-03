#ifndef INFANT_ITEM_HPP
#define INFANT_ITEM_HPP

#include <QJsonObject>

#include "person_item.hpp"

namespace Data
{
namespace People
{
struct infant_item : public person_item
{
    infant_item();

    const constexpr char* key() { return "infant"; };
    static const constexpr auto qmlName{"Infant"};

    enum sexes
    {
        M = 0,
        F
    };

    sexes sex{sexes(M)};

    enum roles
    {
        // following person_items roles
        SexRole = Qt::UserRole + 4
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject &json) const;
};

}
}

#endif // INFANT_ITEM_HPP
