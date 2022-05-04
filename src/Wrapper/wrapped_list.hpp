#ifndef WRAPPED_LIST_HPP
#define WRAPPED_LIST_HPP

#include <QObject>

#include <wobjectdefs.h>

#include <base_wrapper.hpp>

class QQmlContext;

class Outer;

namespace Service
{
class access;
}

namespace Data
{
template <typename Outer>
class item_list;

namespace Wrapper
{

template <typename Inner>
class wrapped_list : public base_wrapper<Inner>
{
    W_OBJECT(wrapped_list)

public:
    explicit wrapped_list(Service::access* srv,
                 QQmlContext* context = nullptr);

    void makeConnections() const;
    void get() const;
};

}
}

#include "wrapped_list.cpp"
#endif // WRAPPED_LIST_HPP
