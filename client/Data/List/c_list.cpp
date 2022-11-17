#pragma once
#include <QJsonDocument>
#include "qjsonarray.h"

#include <wobjectimpl.h>

#include "c_list.hpp"

namespace Data
{
W_OBJECT_IMPL(c_list<T>, template <typename T>)

template <typename T>
c_list<T>::c_list(QObject* parent)
    : c_simple_list<T>{parent}
{
}

template<typename T>
void c_list<T>::complitionChecks() const
{
    this->connect(this, &c_list<T>::postItemsAppended,
            this, &c_list::checkCompleted);

    this->connect(this, &c_list<T>::postItemsRemoved,
            this, &c_list::checkCompleted);

    this->connect(this, &c_list<T>::dataChangedAt,
            this, &c_list::checkCompleted);
}

template <typename T>
void c_list<T>::read(const Json::Value& array)
{
    item_list<T>::read(array);
    emit c_base_data::loaded();
}

template <typename T>
void c_list<T>::read(const QByteArray& bytes)
{
    const auto json = QJsonDocument::fromJson(bytes).array();
    read(json);
}

template<typename T>
void c_list<T>::appendWith(const Json::Value& json)
{
    emit this->preItemsAppended(1);

    T item{};
    item.read(json);
    this->m_items.push_back(item);

    emit this->postItemsAppended();
}


template<typename T>
void c_list<T>::appendWith(int id)
{
    emit this->preItemsAppended(1);

    T item{};
    item.id = id;
    this->m_items.push_back(item);

    emit this->postItemsAppended();
}

template<typename T>
bool c_list<T>::setItemAtId(int id, const T& item)
{
    int index{this->index_at_id(id)};

    if (index == -1)
        return false;

    this->m_items[index] = item;
    emit this->dataChangedAt(index);
    return true;
}

template<typename T>
void c_list<T>::set_list(const std::vector<T>& list)
{
    clear();

    emit this->preItemsAppended(list.size());

    this->m_items = list;

    emit this->postItemsAppended();
}

template<typename T>
void c_list<T>::clear()
{
    emit this->preItemsRemoved(0, this->m_items.size() - 1);

    this->m_items.clear();

    emit this->postItemsRemoved();
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

    emit this->preItemsRemoved(index, index);

    this->m_items.erase(this->m_items.begin() + index);

    emit this->postItemsRemoved();
}

}
