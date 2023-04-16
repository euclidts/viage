#pragma once
#include "s_infant.hpp"
#include <drogon/orm/Field.h>

namespace Data
{
namespace People
{
template <typename T>
s_infant<T>::s_infant()
    : infant_item<T>{}
    , s_person<T>{}
{
}

template <typename T>
void s_infant<T>::set(const Row& row)
{
    s_person<T>::set(row);

    try
    {
        if (!row["Sex"].isNull())
            infant_item<T>::sex = senior_citizen_item::sexes(row["Sex"].as<int>());
    }
    catch (...) {}
}

template <typename T>
const std::string s_infant<T>::fields() const
{
    return s_person<T>::fields() +
            ", Sex = " + std::to_string(infant_item<T>::sex);
}

}
}
