#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <vector>
#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
template <typename T>
class item_list : virtual public base_data
{
public:
    item_list();
    T item_at_id(int id) const;

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;

private:
    void writeWithKey(Json::Value& json) const override;
    int index_at_id(int id) const noexcept;

    std::vector<T> m_items;
};
}

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
