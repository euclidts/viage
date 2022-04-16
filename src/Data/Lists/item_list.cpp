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
    : base_list<T>{parent}
{
    std::string str{T().key()};
    str += 's';

    auto key_str = new char[str.length() + 1];
    strcpy(key_str, str.c_str());
    items_key = key_str;

    str = T::qmlName;
    str += "List";

    auto qml_str = new char[str.length() + 1];
    strcpy(qml_str, str.c_str());
    qmlName = qml_str;
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

    emit loaded();
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
const QByteArray item_list<T>::toData(const char* parentKey, int parentId)
{
    QJsonArray json{};
    write(json);

    QString str{parentKey};
    str.append("Id");

    QJsonObject data{
        {str, parentId},
        {key(), json}
    };

    QJsonDocument bytes{data};
    return bytes.toJson();
}

}
