#pragma once
#include <Item/infant_item.hpp>

namespace Data
{
namespace People
{
template <typename T>
infant_item<T>::infant_item()
    : person_item<T>()
{
}

template <typename T>
void infant_item<T>::read(const Json::Value& json)
{
    person_item<T>::read(json);

    if (json.isMember("sex") && json["sex"].isInt())
        sex = senior_citizen_item::sexes(json["sex"].asInt());
}

template <typename T>
void infant_item<T>::write(Json::Value &json) const
{
    person_item<T>::write(json);

    json["sex"] = sex;
}

template <typename T>
bool infant_item<T>::is_completed() const
{
    if (!person_item<T>::is_completed())
        return false;

    return true;
}

}
}
