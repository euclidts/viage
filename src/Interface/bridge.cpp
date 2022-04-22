#include <wobjectimpl.h>

#include "bridge.hpp"

namespace Interface
{
W_OBJECT_IMPL(bridge)

void bridge::onLogin(const bool& success)
{
    QMetaObject::invokeMethod(qmlObject,
                              "onLogin",
                              Q_ARG(bool, success));
}
}
