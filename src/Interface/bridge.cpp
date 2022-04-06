#include <wobjectimpl.h>

#include "bridge.hpp"

namespace Interface
{
W_OBJECT_IMPL(bridge)

void bridge::loggedIn(const bool& success)
{
    QMetaObject::invokeMethod(qmlObject,
                              "loggedIn",
                              Q_ARG(bool, success));
}
}
