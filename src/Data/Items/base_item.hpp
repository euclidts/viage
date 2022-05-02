#ifndef BASE_ITEM_HPP
#define BASE_ITEM_HPP

#include <base_data.hpp>

namespace Data
{

class base_item : public base_data
{
    virtual void write(QJsonObject &json) const {};
    virtual void clear() {};

protected:
    explicit base_item(QObject* parent = nullptr);

    virtual void writeWithKey(QJsonObject &json);
};
}

#endif // BASE_ITEM_HPP
