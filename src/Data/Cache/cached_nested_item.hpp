#ifndef CACHED_NESTED_ITEM_HPP
#define CACHED_NESTED_ITEM_HPP

#include <wobjectdefs.h>

#include <Cache/cached_list.hpp>

class QQmlContext;

namespace Data
{
class data_notifyer;

namespace Cache
{
class cache;

template <typename Inner, typename Outer>
class cached_nested_item : protected cached_list<Inner>
{
    W_OBJECT(cached_nested_item)

public:
    cached_nested_item(cache* storage, Service::access *srv,
                item_list<Outer>* parentList,
                QQmlContext* context);

protected:
    std::string makeKey(item_list<Outer>* parentList);
    std::string makeKey(item_list<Outer>* parentList, int index);
};

}
}

#include "cached_nested_item.cpp"
#endif // CACHED_NESTED_ITEM_HPP
