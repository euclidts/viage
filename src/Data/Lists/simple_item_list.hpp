#ifndef SIMPLE_simple_item_list_H
#define SIMPLE_simple_item_list_H

#include <QDebug>
#include <QObject>
#include <QVector>

#include <wobjectdefs.h>

#include "base_list.hpp"
#include "base_data.hpp"

namespace Data
{
template <typename T>
class simple_item_list : public base_list<T>
{
    W_OBJECT(simple_item_list)

public:
    explicit simple_item_list(QObject* parent = nullptr);

    const constexpr char* key() override { return items_key; };
    const char* qmlName;
    static const constexpr auto uri{T::uri};

protected:
    const char* items_key;
};
};

#include "simple_item_list.cpp"
#endif // SIMPLE_simple_item_list_H
