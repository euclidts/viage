#ifndef SENIOR_CITIZEN_ITEM_H
#define SENIOR_CITIZEN_ITEM_H

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
namespace People
{

#define AGE_MIN 70
#define AGE_MAX 120

struct senior_citizen_item : virtual public base_data
{
    senior_citizen_item();

    static const constexpr char* key() { return "seniorCitizen"; };

    std::string birthDay{""};

    enum sexes{ M, F };

    sexes sex{sexes(M)};
};

}
}

#endif // SENIOR_CITIZEN_ITEM_H
