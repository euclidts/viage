#ifndef CONTACT_ITEM_HPP
#define CONTACT_ITEM_HPP

#include "infant_item.hpp"

namespace Data
{
namespace People
{
struct contact_item : virtual public infant_item<contact_item>
{   
    static const constexpr char* key() noexcept { return "contact"; };
    static const constexpr auto table{"Contact"};

    bool isInfant{false};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;

protected:
    contact_item();
};

}
}

#endif // CONTACT_ITEM_HPP
