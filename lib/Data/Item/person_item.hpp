#ifndef PERSON_ITEM_HPP
#define PERSON_ITEM_HPP

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
namespace People
{
struct person_item : virtual public base_data
{
    int id{0};
    std::string firstName{""},
    lastName{""},
    phone{"+41"},
    eMail{""};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

protected:
    person_item();

    bool is_completed() const override;
};

}
}

#endif // PERSON_ITEM_HPP
