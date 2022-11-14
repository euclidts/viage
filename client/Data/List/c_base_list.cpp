#pragma once
#include <QVector>
#include <wobjectimpl.h>

#include "c_base_list.hpp"

namespace Data
{
W_OBJECT_IMPL(c_base_list<T>, template <typename T>)

template <typename T>
c_base_list<T>::c_base_list(QObject* parent)
    : c_base_data{parent}
    , item_list<T>()
{
}

template <typename T>
QVector<T> c_base_list<T>::items() const
{
    return QVector<T>(this->m_items.begin(), this->m_items.end());
}

template<typename T>
T c_base_list<T>::item_at(int index) const
{
    return this->m_items[index];
}

template <typename T>
bool c_base_list<T>::setItemAt(int index, const T& item)
{
    if (index < 0 || index >= this->m_items.size())
        return false;

    this->m_items[index] = item;

    emit dataChangedAt(index);

    return true;
}

template <typename T>
void c_base_list<T>::appendItems(int number)
{
    emit preItemsAppended(number);

    for (int i = 0; i < number; i++)
        this->m_items.push_back(T{});

    emit postItemsAppended();
}

template<typename T>
void c_base_list<T>::removeItems(int first, int last)
{
    emit preItemsRemoved(first, last);

    this->m_items.erase(this->m_items.begin() + first,
                        std::next(this->m_items.begin() + last));

    emit postItemsRemoved();
}

template<typename T>
void c_base_list<T>::removeItems(int number)
{
    const auto count = this->m_items.size();

    removeItems(count - number, count - 1);
}

}
