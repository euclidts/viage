#ifndef OWNER_ITEM_HPP
#define OWNER_ITEM_HPP

#include "infant_item.hpp"
#include <Item/address_item.hpp>

namespace Data
{
struct url_list;

namespace Places
{
struct address_item;
}

namespace People
{

struct owner_item : virtual public infant_item
{
    owner_item();

    const char* key() const noexcept override { return "owner"; };
    static const constexpr auto table{"Owner"};

    Places::address_item* address;
    std::string birthDay{""};

    enum civilStates
    {
        None,
        Single,
        Maried,
        Registered,
        Separated,
        Divorced,
        Disolved,
        Widow
    };

    civilStates civilStatus{None};
    std::string avs{""};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // OWNER_ITEM_HPP
