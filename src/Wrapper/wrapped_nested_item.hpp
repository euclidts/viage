#ifndef WRAPPED_NESTED_ITEM_HPP
#define WRAPPED_NESTED_ITEM_HPP

#include <wobjectdefs.h>

#include "wrapped_list.hpp"

class QQmlContext;

namespace Data
{
class data_notifyer;

namespace Wrapper
{
template <typename Inner, typename Outer>
class wrapped_nested_item : public wrapped_list<Inner>
{
    W_OBJECT(wrapped_nested_item)

public:
    explicit wrapped_nested_item(Service::access *srv,
                       QQmlContext* context = nullptr);

    void makeConnections(item_list<Outer>* parentList);

protected:
    std::string makeKey(item_list<Outer>* parentList);
    std::string makeKey(item_list<Outer>* parentList, int id);
};

}
}

#include "wrapped_nested_item.cpp"
#endif // WRAPPED_NESTED_ITEM_HPP
