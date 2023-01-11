#ifndef C_INFANT_HPP
#define C_INFANT_HPP

#include "qnamespace.h"
#include "c_person.hpp"
#include <Item/infant_item.hpp>

namespace Data
{
namespace People
{
template <typename T>
struct c_infant : public virtual infant_item<T>
                , public c_person<T>
{   
    enum roles
    {
        // following infant_item roles
        SexRole = Qt::UserRole + 6
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const Json::Value& json) { infant_item<T>::read(json); }
    void write(Json::Value& json) const { infant_item<T>::write(json); }

    bool is_completed() const { return infant_item<T>::is_completed(); };

protected:
    c_infant();
};

}
}

#include "c_infant.cpp"
#endif // C_INFANT_HPP
