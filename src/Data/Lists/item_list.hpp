#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <QDebug>
#include <QObject>
#include <QVector>

#include <wobjectdefs.h>

#include "simple_item_list.hpp"

namespace Data
{
template <typename T>
class item_list : public simple_item_list<T>
{
    W_OBJECT(item_list)

public:
    explicit item_list(QObject* parent = nullptr);

    void add()
    W_SIGNAL(add)
    void addIn(int parentId)
    W_SIGNAL(addIn, parentId)
    void addInWith(int parentId, const QJsonObject& obj)
    W_SIGNAL(addInWith, parentId, obj)

    void read(const QJsonArray& json);
    void read(const QByteArray& bytes);
    void write(QJsonArray& json) const;

private:
    void writeWithKey(QJsonObject &json) override;

};
};

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
