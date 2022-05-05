#ifndef BASE_LIST_HPP
#define BASE_LIST_HPP

#include <QVector>

#include <base_data.hpp>

namespace Data
{
template <typename T>
class base_list : public base_data
{
    W_OBJECT(base_list)

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
    explicit base_list(QObject* parent = nullptr);

    std::vector<T> m_items;
};

};

#include "base_list.cpp"
#endif // BASE_LIST_HPP
