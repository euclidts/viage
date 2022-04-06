#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <QDebug>
#include <QObject>
#include <QVector>

#include <wobjectdefs.h>

#include "base_list.hpp"

namespace Data
{
template <typename T>
class item_list : public base_list<T>
{
    W_OBJECT(item_list)

public:
    explicit item_list(QObject* parent = nullptr);

    const char* key() { return items_key; };
    const char* qmlName;
    static const constexpr auto uri{T::uri};

    void validate(int parentIndex)
    W_SIGNAL(validate, parentIndex)

    void loadFrom(int parentIndex)
    W_SIGNAL(loadFrom, parentIndex)

    void loaded()
    W_SIGNAL(loaded)

    void add()
    W_SIGNAL(add)
    void addIn(int parentIndex)
    W_SIGNAL(addIn, parentIndex)

    void read(const QJsonArray& json);
    void read(const QByteArray& bytes);
    void write(QJsonArray& json) const;

    const QByteArray toData(int id);

private:
    const char* items_key;
};
};

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
