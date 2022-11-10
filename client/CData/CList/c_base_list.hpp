#ifndef C_BASE_LIST_HPP
#define C_BASE_LIST_HPP

#include <QVector>
#include <wobjectdefs.h>
#include <c_base_data.hpp>
#include <List/item_list.hpp>

namespace Data
{
template <typename T>
class c_base_list : public item_list<T>
                  , public c_base_data
{
    W_OBJECT(c_base_list<T>)

public:
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

protected:
    explicit c_base_list(QObject* parent = nullptr);
};

};

#include "c_base_list.cpp"
#endif // C_BASE_LIST_HPP
