#ifndef CACHED_NESTED_LIST_HPP
#define CACHED_NESTED_LIST_HPP

#include <wobjectdefs.h>

#include <Cache/cached_nested_item.hpp>

class QQmlContext;

namespace Data
{
class data_notifyer;

namespace Cache
{
class cache;

template <typename Inner, typename Outer>
class cached_nested_list : protected cached_nested_item<Inner, Outer>
{
    W_OBJECT(cached_nested_list)

public:
    cached_nested_list(cache* storage, Service::access *srv,
                item_list<Outer>* parentList,
                QQmlContext* context);
};

}
}

#include "cached_nested_list.cpp"
#endif // CACHED_NESTED_LIST_HPP
