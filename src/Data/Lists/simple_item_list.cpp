#pragma once
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <array>

#include <wobjectimpl.h>

#include "simple_item_list.hpp"

namespace Data
{
W_OBJECT_IMPL(simple_item_list<T>, template <typename T>)

template <typename T>
simple_item_list<T>::simple_item_list(QObject* parent)
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

}
