#pragma once
#include <QVector>
#include <wobjectimpl.h>

#include "base_list.hpp"

namespace Data
{
W_OBJECT_IMPL(base_list<T>, template <typename T>)

template <typename T>
base_list<T>::base_list(QObject* parent)
    : QObject{parent}
{
}

template <typename T>
QVector<T> base_list<T>::items() const
{
    return QVector<T>(m_items.begin(), m_items.end());
}

template <typename T>
bool base_list<T>::setItemAt(int index, const T& item)
{
    if (index < 0 || index >= m_items.size())
        return false;

    m_items[index] = item;

    emit dataChangedAt(index);

    return true;
}

template <typename T>
void base_list<T>::appendItems(int number)
{
    emit preItemsAppended(number);

    for (int i = 0; i < number; i++)
        m_items.push_back(T{});

    emit postItemsAppended();
}

template<typename T>
void base_list<T>::appendWith(const QJsonObject& json)
{
    emit preItemsAppended(1);

    T item{};
    item.read(json);
    m_items.push_back(item);

    emit postItemsAppended();
}


template<typename T>
void base_list<T>::appendWith(int id)
{
    emit preItemsAppended(1);

    T item{};
    item.id = id;
    m_items.push_back(item);

    emit postItemsAppended();
}

template<typename T>
T base_list<T>::item_at(int index) const
{
    return m_items[index];
}

template<typename T>
void base_list<T>::removeItems(int first, int last)
{
    emit preItemsRemoved(first, last);

    m_items.erase(m_items.begin() + first, std::next(m_items.begin() + last));

    emit postItemsRemoved();
}

template<typename T>
void base_list<T>::set_list(const std::vector<T>& list)
{
    emit preItemsRemoved(0, m_items.size() - 1);

    m_items.clear();

    emit postItemsRemoved();
    emit preItemsAppended(list.size());

    m_items = list;

    emit postItemsAppended();
}

}
