#pragma once

#include <wobjectimpl.h>

#include "c_list.hpp"

namespace Data
{
W_OBJECT_IMPL(c_list<T>, template <typename T>)

template <typename T>
c_list<T>::c_list(QObject* parent)
    : item_list<T>{}
    , c_base_data{parent}
{
    std::string str{T::qmlName};
    str += "List";

    auto qml_str = new char[str.length() + 1];
    strcpy(qml_str, str.c_str());
    qmlName = qml_str;
}

template <typename T>
QVector<T> c_list<T>::items() const
{
    return QVector<T>(this->m_items.begin(), this->m_items.end());
}

template<typename T>
T c_list<T>::item_at(int index) const
{
    return this->m_items[index];
}

template <typename T>
bool c_list<T>::setItemAt(int index, const T& item)
{
    if (index < 0 || index >= this->size())
        return false;

    this->m_items[index] = item;

    emit dataChangedAt(index);

    return true;
}

template <typename T>
void c_list<T>::appendItems(int number)
{
    emit preItemsAppended(number);

    for (int i = 0; i < number; i++)
        this->m_items.push_back(T{});

    emit postItemsAppended();
}

template<typename T>
void c_list<T>::removeItems(int first, int last)
{
    emit preItemsRemoved(first, last);

    this->m_items.erase(this->m_items.begin() + first,
                        std::next(this->m_items.begin() + last));

    emit postItemsRemoved();
}

template<typename T>
void c_list<T>::removeItems(int number)
{
    const auto count = this->size();

    removeItems(count - number, count - 1);
}
template<typename T>
void c_list<T>::complitionChecks() const
{
    connect(this, &c_list::postItemsAppended,
            this, &c_list::checkCompleted);

    connect(this, &c_list::postItemsRemoved,
            this, &c_list::checkCompleted);

    connect(this, &c_list::dataChangedAt,
            this, &c_list::checkCompleted);
}

template <typename T>
void c_list<T>::read(const Json::Value& array)
{
    item_list<T>::read(array);
    emit c_base_data::loaded();
}

template<typename T>
void c_list<T>::appendWith(const Json::Value& json)
{
    emit preItemsAppended(1);

    T item{};
    item.read(json);
    this->m_items.push_back(item);

    emit postItemsAppended();
}

template<typename T>
void c_list<T>::appendWith(int id)
{
    emit preItemsAppended(1);

    T item{};
    item.id = id;
    this->m_items.push_back(item);

    emit postItemsAppended();
}

template<typename T>
bool c_list<T>::setItemAtId(int id, const T& item)
{
    int index{this->index_at_id(id)};

    if (index == -1)
        return false;

    this->m_items[index] = item;
    emit dataChangedAt(index);
    return true;
}

template<typename T>
void c_list<T>::set_list(const std::vector<T>& list)
{
    clear();

    emit preItemsAppended(list.size());

    this->m_items = list;

    emit postItemsAppended();
}

template<typename T>
void c_list<T>::clear()
{
    emit preItemsRemoved(0, this->size() - 1);

    this->m_items.clear();

    emit postItemsRemoved();
}

template<typename T>
void c_list<T>::checkCompleted()
{
    if (this->m_items.empty())
    {
        this->setCompleted(false);
        return;
    }

    for (const auto& item : this->m_items)
        if (!item.is_completed())
        {
            this->setCompleted(false);
            return;
        }

    this->setCompleted(true);
}

template<typename T>
void c_list<T>::erase(int id)
{
    int index{this->index_at_id(id)};

    if (index == -1)
        return;

    emit preItemsRemoved(index, index);

    this->m_items.erase(this->m_items.begin() + index);

    emit postItemsRemoved();
}

template<typename T>
void c_list<T>::read(const QByteArray &bytes)
{
    c_base_data::read(bytes);
}

}
