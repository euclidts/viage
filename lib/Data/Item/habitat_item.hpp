#ifndef HABITAT_ITEM_HPP
#define HABITAT_ITEM_HPP

#include <json/json.h>

#include "base_data.hpp"
#include "address_item.hpp"

namespace Data
{
namespace Places
{
class habitat_item : virtual public base_data
{
public:
    explicit habitat_item();

    const char* key() const noexcept override { return "habitat"; };

    enum habitatTypes
    {
        None,
        DetachedHouse,
        AdjacentHouse,
        Appartement
    };

    Places::address_item address;
    habitatTypes habitatType{None};
    int rooms{2};
    int rawSurface{50};
    int surface{50};
    int m2Constructed{25};
    int m2Available{25};
    int m3s{9000};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // HABITAT_ITEM_HPP
