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
void s_infant<T>::read(const nanodbc::result& res)
{
    s_person<T>::read(res);

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
  return "Sex = '"
          + std::to_string(infant_item<T>::sex) +
          "'";
}

}
}
