#ifndef CONTACT_ITEM_H
#define CONTACT_ITEM_H

#include "infant_item.hpp"

namespace Data
{
namespace People
{
struct contact_item : virtual public infant_item
{   
    contact_item();

    static const constexpr char* key() { return "contact"; };

    bool isInfant{false};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // CONTACT_ITEM_H
