#ifndef C_LIST_HPP
#define C_LIST_HPP

#include <json/value.h>
#include <wobjectdefs.h>

#include <c_base_data.hpp>
#include <item_list.hpp>

namespace Data
{
template <typename T>
class c_list final : public c_base_data<item_list<T>>
                   , public item_list<T>
{    
    W_OBJECT(c_list)

public:
    c_list(QObject* parent = nullptr);

    const char* qmlName;
    static const constexpr auto uri{T::uri};

    QVector<T> items() const;
    T item_at(int index) const;

    bool setItemAt(int index, const T& item);

    void preItemsAppended(int number = 1)
    W_SIGNAL(preItemsAppended, number)
    void postItemsAppended()
    W_SIGNAL(postItemsAppended)

    void appendItems(int number = 1);
    W_SLOT(appendItems, (int))

    void preItemsRemoved(int first, int last)
    W_SIGNAL(preItemsRemoved, first, last)
    void postItemsRemoved()
    W_SIGNAL(postItemsRemoved)

    void dataChangedAt(int index)
    W_SIGNAL(dataChangedAt, index)

    void removeItems(int first, int last);
    W_SLOT(removeItems, (int, int))

    void removeItems(int number = 1);
    W_SLOT(removeItems, (int))

    bool setItemAtId(int id, const T& item);
    void set_list(const std::vector<T>& list);
    void clear() override;
    W_INVOKABLE(clear)

    void add()
    W_SIGNAL(add)
    void addWith(const QJsonObject& obj)
    W_SIGNAL(addWith, obj)
    void addIn(int parentId)
    W_SIGNAL(addIn, parentId)
    void addInWith(int parentId, const QJsonObject& obj)
    W_SIGNAL(addInWith, parentId, obj)

    void remove(int id)
    W_SIGNAL(remove, id)

    void appendWith(int id);
    void appendWith(const Json::Value& json);

    void erase(int id);

    void read(const Json::Value& json) override;

    void complitionChecks() const;

private:
    void checkCompleted() override;
};

}

#include "c_list.cpp"
#endif // C_LIST_HPP
