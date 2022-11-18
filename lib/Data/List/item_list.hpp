#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <vector>
#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
template <typename T>
class item_list : public virtual base_data
{
public:
    item_list();

    const char* key() const { return items_key; };

    void set_list(const std::vector<T>& list);
    T item_at_id(int id) const;

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    bool is_completed() const override;

protected:
    void writeWithKey(Json::Value& json) const;
    int index_at_id(int id) const noexcept;

    std::vector<T> m_items;
    const char* items_key;
};
}

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
