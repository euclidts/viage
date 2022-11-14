#pragma once
#include <array>

#include "c_simple_list.hpp"

namespace Data
{
template <typename T>
c_simple_list<T>::c_simple_list(QObject* parent)
    : c_base_list<T>{parent}
{
    std::string str{T().key()};

    if (str.back() == 'y')
    {
        str.pop_back();
        str += "ie";
    }

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
