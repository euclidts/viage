#ifndef WRAPPED_NESTED_LIST_HPP
#define WRAPPED_NESTED_LIST_HPP

#include "wrapped_nested_item.hpp"

class QQmlContext;

namespace Data
{
class data_notifyer;
}

namespace Wrapper
{
template <typename Inner, typename Outer>
class wrapped_nested_list : public wrapped_nested_item<Inner, Outer>
{
public:
    explicit wrapped_nested_list(Interface::netManager *manager,
                Data::c_list<Outer>* parentList,
                QQmlContext* context = nullptr);

private:
    const std::string key;
    const std::string parent_key_id;
    void add_in_with(int id, const Json::Value& obj = {});
};

}

#include "wrapped_nested_list.cpp"
#endif // WRAPPED_NESTED_LIST_HPP
