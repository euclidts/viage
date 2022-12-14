#ifndef C_ADDRESS_HPP
#define C_ADDRESS_HPP

#include "qnamespace.h"

namespace Data
{
namespace Places
{
struct address_item;

struct c_address
{
    explicit c_address(address_item* ai);

    enum roles
    {
        // following after owner_item roles
        StreetRole = Qt::UserRole + 10,
        ZipRole,
        CantonRole,
        CityRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

protected:
    address_item* address;
};

}
}

#endif // C_ADDRESS_HPP
