#pragma once
#include <wobjectimpl.h>

#include "c_base_data.hpp"
#include <utils.hpp>

namespace Data
{
W_OBJECT_IMPL(c_base_data<T>, template <typename T>)

template <typename T>
c_base_data<T>::c_base_data(QObject* parent)
    : QObject{parent}
    , base_data<T>{}
{
}

template <typename T>
const QByteArray c_base_data<T>::toData(const char* parentKey, int parentId)
{
    std::string str{parentKey};
    str.append("Id");

    Json::Value data;
    data[str] = parentId;

    writeWithKey<T>(data);

    return Utils::to_QByteArray(data);
}

template <typename T>
const QByteArray c_base_data<T>::toData(int parentId)
{
    Json::Value data;
    data["Id"] = parentId;

    base_data<T>::writeWithKey(data);

    return Utils::to_QByteArray(data);
}

template <typename T>
bool c_base_data<T>::getCompleted() const
{
    return completed;
}

template <typename T>
void c_base_data<T>::setCompleted(bool newCompleted)
{
    if (completed == newCompleted)
        return;
    completed = newCompleted;
    emit completedChanged();
}

}
