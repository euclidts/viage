#ifndef INFANT_ITEM_HPP
#define INFANT_ITEM_HPP

#include <json/json.h>

#include "person_item.hpp"
#include "senior_citizen_item.hpp" // needed for sexes enum

namespace Data
{
namespace People
{
struct infant_item : virtual public person_item
{   
    infant_item();

    senior_citizen_item::sexes sex{senior_citizen_item::M};

    void read(const Json::Value& json);
    void write(Json::Value& json) const;

    bool is_completed() const;
};

}
}

#endif // INFANT_ITEM_HPP
