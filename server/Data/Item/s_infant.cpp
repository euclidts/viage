#pragma once
#include "s_infant.hpp"

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
void s_infant<T>::set(const nanodbc::result& res)
{
    s_person<T>::set(res);

    try
    {
        if (!res.is_null("Sex"))
            infant_item<T>::sex = senior_citizen_item::sexes(res.get<int>("Sex"));
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
