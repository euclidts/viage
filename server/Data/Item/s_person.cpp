#pragma once
#include "s_person.hpp"
#include <drogon/orm/Field.h>

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
void s_person<T>::set(const Row& row)
{
    try
    {
        if (!row["Id"].isNull())
            person_item<T>::id = row["Id"].as<int>();
    }
    catch (...) {}

    try
    {
        if (!row["FirstName"].isNull())
            person_item<T>::firstName = row["FirstName"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["LastName"].isNull())
            person_item<T>::lastName = row["LastName"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["Phone"].isNull())
            person_item<T>::phone = row["Phone"].as<std::string>();
    }
    catch (...) {}

    try
    {
        if (!row["EMail"].isNull())
            person_item<T>::eMail = row["EMail"].as<std::string>();
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
