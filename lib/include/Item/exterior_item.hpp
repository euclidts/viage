#ifndef EXTERIOR_ITEM_HPP
#define EXTERIOR_ITEM_HPP

#include <json/json.h>
#include "base_data.hpp"

namespace Data
{
namespace Places
{
class exterior_item : virtual public base_data
{
public:
    exterior_item();

    const char* key() const noexcept override { return "exterior"; };
    static const constexpr auto table{"ExteriorItem"};

    enum parkingTypes
    {
        NoParking = 0,
        Bike = 1,
        Car = 2,
        Indoor = 4,
        Outdoor = 8,
        individual = 16,
        Colective = 32
    };

    enum equipements
    {
        None = 0,
        Health = 1,
        Food = 2,
        Education = 4,
        Leasure = 8,
        Shops = 16,
        Transports = 32
    };

    bool hasParking{false};
    int parkingSpots{0};
    parkingTypes parkingType{NoParking};
    int parkingSurface{0};
    std::string terrainDescription{""};
    int terrainSurface{50};
    equipements equipement{None};
    int rating{0};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // EXTERIOR_ITEM_HPP
