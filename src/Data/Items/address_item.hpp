#ifndef ADDRESS_ITEM_H
#define ADDRESS_ITEM_H

#include <QJsonObject>

namespace Data
{
namespace Places
{
struct address_item
{
    address_item();

    QString street{""};
    QString city{""};
    int zip{9000};
    QString canton{"Appenzell"};

    enum roles
    {
        // following after owner_item roles
        StreetRole = Qt::UserRole + 9,
        ZipRole,
        CantonRole,
        CityRole
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

#endif // ADDRESS_ITEM_H
