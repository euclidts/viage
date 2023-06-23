#pragma once

#include "qqml.h"
#include <QQmlContext>

#include <wobjectimpl.h>

#include <Interface/bridge.hpp>
#include "base_wrapper.hpp"

namespace Wrapper
{
W_OBJECT_IMPL(base_wrapper<Inner>, template <typename Inner>)

template <typename Inner>
base_wrapper<Inner>::base_wrapper()
    : QObject{}
    , inner{new Inner{}}
{
    registerToQml();
}

template<typename Inner>
void base_wrapper<Inner>::registerToQml() const
{
    qmlRegisterUncreatableType<Inner>(inner->uri, 1, 0, inner->qmlName, "");
    Interface::bridge::instance().context()->setContextProperty(inner->key, inner);
}

template<typename Inner>
Inner* base_wrapper<Inner>::get_inner() const
{
    return inner;
}
} // namespace Wrapper
