#ifndef ADDRESS_ITEM_H
#define ADDRESS_ITEM_H

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
namespace Places
{
struct address_item : public base_data
{
    address_item();

    const char* key() const override { return "address"; };

    std::string street{""};
    std::string city{""};
    int zip{9000};
    std::string canton{"Appenzell"};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}
}

#endif // ADDRESS_ITEM_H
