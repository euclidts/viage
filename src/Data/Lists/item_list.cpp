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

}
