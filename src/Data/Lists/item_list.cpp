#pragma once
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <wobjectimpl.h>

#include "item_list.hpp"

namespace Data
{
W_OBJECT_IMPL(item_list<T>, template <typename T>)

template <typename T>
item_list<T>::item_list(QObject* parent)
    : simple_item_list<T>{parent}
{
}

template<typename T>
void item_list<T>::complitionChecks() const
{
    this->connect(this, &item_list<T>::postItemsAppended,
            this, &item_list::checkCompleted);

    this->connect(this, &item_list<T>::postItemsRemoved,
            this, &item_list::checkCompleted);

    this->connect(this, &item_list<T>::dataChangedAt,
            this, &item_list::checkCompleted);
}


template<typename T>
T item_list<T>::item_at_id(int id) const
{
    T item{};

    int index{index_at_id(id)};

    if (index != -1)
        item = this->m_items[index];

    return item;
}

template <typename T>
void item_list<T>::read(const QJsonArray& array)
{
    std::vector<T> vec{};

    for (const auto& json : array)
    {
        T item{};
        item.read(json.toObject());
        vec.push_back(item);
    }

    this->set_list(vec);

    emit base_data::loaded();
}

template <typename T>
void item_list<T>::read(const QByteArray& bytes)
{
    const auto json = QJsonDocument::fromJson(bytes).array();
    read(json);
}

template <typename T>
void item_list<T>::write(QJsonArray& json) const
{
    for (const auto& item : this->m_items)
    {
        QJsonObject obj{};
        item.write(obj);
        json.push_back(obj);
    }
}

template<typename T>
void item_list<T>::writeWithKey(QJsonObject &json)
{
    QJsonArray array{};
    write(array);

    json[this->key()] = array;
}

template<typename T>
void item_list<T>::appendWith(const QJsonObject& json)
{
    emit this->preItemsAppended(1);

    T item{};
    item.read(json);
    this->m_items.push_back(item);

    emit this->postItemsAppended();
}


template<typename T>
void item_list<T>::appendWith(int id)
{
    emit this->preItemsAppended(1);

    T item{};
    item.id = id;
    this->m_items.push_back(item);

    emit this->postItemsAppended();
}

template<typename T>
bool item_list<T>::setItemAtId(int id, const T& item)
{
    int index{index_at_id(id)};

    if (index == -1)
        return false;

    this->m_items[index] = item;
    emit this->dataChangedAt(index);
    return true;
}

template<typename T>
void item_list<T>::set_list(const std::vector<T>& list)
{
    clear();

    emit this->preItemsAppended(list.size());

    this->m_items = list;

    emit this->postItemsAppended();
}

template<typename T>
void item_list<T>::clear()
{
    emit this->preItemsRemoved(0, this->m_items.size() - 1);

    this->m_items.clear();

    emit this->postItemsRemoved();
}

template<typename T>
void item_list<T>::checkCompleted()
{
    if(this->m_items.empty())
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
void item_list<T>::erase(int id)
{
    int index{index_at_id(id)};

    if (index == -1)
        return;

    emit this->preItemsRemoved(index, index);

    this->m_items.erase(this->m_items.begin() + index);

    emit this->postItemsRemoved();
}

template<typename T>
int item_list<T>::index_at_id(int id) const noexcept
{
    int index{-1};

    for (int i = 0; i < this->m_items.size(); i++)
        if (this->m_items[i].id == id)
        {
            index = i;
            break;
        }

    return index;
}

}
