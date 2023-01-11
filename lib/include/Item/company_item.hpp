#ifndef COMPANY_ITEM_HPP
#define COMPANY_ITEM_HPP

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
template <typename T>
struct item_list;

struct company_item : virtual public base_data<company_item>
{
    company_item();

    static const constexpr char* key() noexcept { return "company"; };
    static const constexpr auto foreign_key{"CompanyId"};

    int id{0};
    std::string name{};
    Json::Value teams;

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;
};

}

#endif // COMPANY_ITEM_HPP
