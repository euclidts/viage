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

    const char* key() const noexcept override { return "contact"; };
    static const constexpr auto table{"Contact"};

    bool isInfant{false};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // CONTACT_ITEM_H
