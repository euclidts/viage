#ifndef WRAPPED_LIST_HPP
#define WRAPPED_LIST_HPP

#include <base_wrapper.hpp>

class QQmlContext;

class Outer;

namespace Interface
{
class netManager;
}

namespace Data
{
template <typename Outer>
class item_list;
}

namespace Wrapper
{

template <typename Inner>
class wrapped_list : public base_wrapper<Inner>
{
public:
    explicit wrapped_list(Interface::netManager* manager,
                          QQmlContext* context = nullptr);

    void makeConnections() const;
    void get() const;
};

}

#include "wrapped_list.cpp"
#endif // WRAPPED_LIST_HPP
