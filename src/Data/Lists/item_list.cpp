#pragma once
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <array>

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
T item_list<T>::item_at_id(int id) const
{
    T item{};

    for (const auto& obj : this->m_items)
        if (obj.id == id)
            item = obj;

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
    for (int i = 0; i < this->m_items.size(); i++)
    {
        if (this->m_items[i].id == id)
        {
            this->m_items[i] = item;
            emit this->dataChangedAt(i);
            return true;
        }
    }

    return false;
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

}
