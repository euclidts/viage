#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <QDebug>
#include <QObject>
#include <QVector>

#include <wobjectdefs.h>

#include "base_list.hpp"
#include "base_data.hpp"

namespace Data
{
template <typename T>
class item_list : public base_list<T>
{
    W_OBJECT(item_list)

public:
    explicit item_list(QObject* parent = nullptr);

    const constexpr char* key() override { return items_key; };
    const char* qmlName;
    static const constexpr auto uri{T::uri};

    void add()
    W_SIGNAL(add)
    void addIn(int parentIndex)
    W_SIGNAL(addIn, parentIndex)
    void addInWith(int parentIndex, const QJsonObject& obj)
    W_SIGNAL(addInWith, parentIndex, obj)

    void read(const QJsonArray& json);
    void read(const QByteArray& bytes);
    void write(QJsonArray& json) const;

protected:
    void writeWithKey(QJsonObject &json) override;

private:
    const char* items_key;
};
};

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
