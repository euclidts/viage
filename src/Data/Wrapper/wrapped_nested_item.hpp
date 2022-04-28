#ifndef WRAPPED_NESTED_ITEM_HPP
#define WRAPPED_NESTED_ITEM_HPP

#include <wobjectdefs.h>

#include <Wrapper/wrapped_list.hpp>

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
    wrapped_nested_item(Service::access *srv,
                       item_list<Outer>* parentList,
                       QQmlContext* context);

protected:
    std::string makeKey(item_list<Outer>* parentList);
    std::string makeKey(item_list<Outer>* parentList, int index);
};

}
}

#include "wrapped_nested_item.cpp"
#endif // WRAPPED_NESTED_ITEM_HPP
