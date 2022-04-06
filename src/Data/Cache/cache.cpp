#pragma once
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonArray>

#include <wobjectimpl.h>

#include "cache.hpp"

namespace Data
{
namespace Cache
{
W_OBJECT_IMPL(cache)

cache::cache()
    : QObject{}
{
}

template <typename T>
void cache::update(const char* parentKey, int index, const T& element, const char* key)
{
    auto jsonArray{value(parentKey).toArray()};
    auto jsonElement{jsonArray.at(index).toObject()};
    jsonElement[key] = element;

    if (jsonArray.size() < index + 1)
        jsonArray.push_back(jsonElement);
    else
        jsonArray.replace(index, jsonElement);

    insert(parentKey, jsonArray);

    print();
}

template<typename T>
void cache::update(int index, const T &element, const char *key)
{
    auto jsonArray{value(key).toArray()};

    if (jsonArray.size() < index + 1)
        jsonArray.push_back(element);
    else
        jsonArray.replace(index, element);

    insert(key, jsonArray);

    print();

}

void cache::print() const
{
    QTextStream(stdout) << "Cache : "
                        << QJsonDocument(*this).toJson();
}

}
}
