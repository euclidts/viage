#pragma once
#include "s_person.hpp"

namespace Data
{
namespace People
{
template <typename T>
s_person<T>::s_person()
    : person_item<T>{}
{
}

template <typename T>
void s_person<T>::set(const nanodbc::result& res)
{
    try
    {
        if (!res.is_null("Id"))
            person_item<T>::id = res.get<int>("Id");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("FirstName"))
            person_item<T>::firstName = res.get<std::string>("FirstName");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("LastName"))
            person_item<T>::lastName = res.get<std::string>("LastName");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("Phone"))
            person_item<T>::phone = res.get<std::string>("Phone");
    }
    catch (...) {}

    try
    {
        if (!res.is_null("EMail"))
            person_item<T>::eMail = res.get<std::string>("EMail");
    }
    catch (...) {}
}

template <typename T>
const std::string s_person<T>::fields() const
{
  return "FirstName = '"
          + person_item<T>::firstName +
          "', LastName = '"
          + person_item<T>::lastName +
          "', Phone = '"
          + person_item<T>::phone +
          "', EMail = '"
          + person_item<T>::eMail +
          "'";
}

}
}
