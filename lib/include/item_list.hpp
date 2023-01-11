#ifndef ITEM_LIST_HPP
#define ITEM_LIST_HPP

#include <vector>
#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
template <typename T>
class item_list : public virtual base_data<item_list<T>>
{
public:
    item_list();

    int size() const;

    static const constexpr char* key() noexcept
    {
        std::string str{T::key()};

        if (str.back() == 'y')
        {
            str.pop_back();
            str += "ie";
        }

        str += 's';

        auto key_str = new char[str.length() + 1];
        strcpy(key_str, str.c_str());
        return key_str;
    };

    void set_list(const std::vector<T>& list);
    T item_at_id(int id) const;

    void read(const Json::Value& json) override;
    virtual void write(Json::Value& json) const override;

    bool is_completed() const override;

protected:
    void writeWithKey(Json::Value& json) const override;
    int index_at_id(int id) const noexcept;

    std::vector<T> m_items{};
};
}

#include "item_list.cpp"
#endif // ITEM_LIST_HPP
