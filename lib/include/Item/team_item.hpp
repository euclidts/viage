#ifndef TEAM_ITEM_H
#define TEAM_ITEM_H

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{

struct team_item : virtual public base_data
{
    team_item();

    const char* key() const noexcept override { return "team"; };
    static const constexpr auto table{"Team"};

    int id{0};
    std::string caption{""};
    bool has_users{false};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}

#endif // TEAM_ITEM_H
