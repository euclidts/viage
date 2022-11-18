#ifndef OWNER_ITEM_HPP
#define OWNER_ITEM_HPP

#include "infant_item.hpp"
#include "address_item.hpp"

namespace Data
{
struct url_list;

namespace People
{

struct owner_item : virtual public infant_item
{
    owner_item();

    static const constexpr char* key() { return "owner"; };

    Places::address_item address;
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
