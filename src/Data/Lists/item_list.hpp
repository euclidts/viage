#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

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
    T item_at_id(int id) const;

    bool setItemAtId(int id, const T& item);
    void set_list(const std::vector<T>& list);
    void clear();
    W_SLOT(clear)

    void add()
    W_SIGNAL(add)
    void addIn(int parentId)
    W_SIGNAL(addIn, parentId)
    void addInWith(int parentId, const QJsonObject& obj)
    W_SIGNAL(addInWith, parentId, obj)

    void appendWith(int id);
    void appendWith(const QJsonObject &json);
    W_SLOT(appendWith, (const QJsonObject&))

    void read(const QJsonArray& json);
    void read(const QByteArray& bytes);
    void write(QJsonArray& json) const;

    void complitionChecks();

private:
    void writeWithKey(QJsonObject &json) override;

    void checkCompleted() override;
};

}

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
