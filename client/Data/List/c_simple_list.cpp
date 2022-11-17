#pragma once
#include <array>

#include "c_simple_list.hpp"

namespace Data
{
template <typename T>
c_simple_list<T>::c_simple_list(QObject* parent)
    : c_base_list<T>{parent}
{
    std::string str{T::qmlName};
    str += "List";

    auto qml_str = new char[str.length() + 1];
    strcpy(qml_str, str.c_str());
    qmlName = qml_str;
}

}
