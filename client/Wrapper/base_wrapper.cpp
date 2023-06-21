#pragma once
#include <QQmlContext>

#include <wobjectimpl.h>

#include "base_wrapper.hpp"

namespace Wrapper
{
W_OBJECT_IMPL(base_wrapper<Inner>, template <typename Inner>)

template <typename Inner>
base_wrapper<Inner>::base_wrapper(QQmlContext* context)
    : QObject{}
    , inner{new Inner{}}
{
    if (context)
        registerToQml(context);
}

template<typename Inner>
void base_wrapper<Inner>::registerToQml(QQmlContext* context) const
{
    qmlRegisterUncreatableType<Inner>(inner->uri, 1, 0, inner->qmlName, "");
    context->setContextProperty(inner->key, inner);
}

template<typename Inner>
Inner* base_wrapper<Inner>::get_inner() const
{
    return inner;
}
} // namespace Wrapper
