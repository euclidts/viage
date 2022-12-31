#pragma once
#include <QQmlContext>

#include <wobjectimpl.h>

#include "base_wrapper.hpp"
#include <netManager.hpp>

namespace Wrapper
{
W_OBJECT_IMPL(base_wrapper<Inner>, template <typename Inner>)

template <typename Inner>
base_wrapper<Inner>::base_wrapper(Interface::netManager* manager,
                                  QQmlContext* context)
    : QObject{}
    , mng(manager)
    , inner{new Inner{}}
{
    if (context)
        registerToQml(context);
}

template<typename Inner>
void base_wrapper<Inner>::registerToQml(QQmlContext* context) const
{
    // use table names as qmlName
    qmlRegisterUncreatableType<Inner>(inner->uri, 1, 0, inner->table, "");
    context->setContextProperty(inner->key(), inner);
}

template<typename Inner>
Inner* base_wrapper<Inner>::get_inner() const
{
    return inner;
}

}
