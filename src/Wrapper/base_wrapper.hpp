#ifndef BASE_WRAPPER_HPP
#define BASE_WRAPPER_HPP

#include <QObject>
#include "qqml.h"
#include <QQmlContext>

#include <wobjectdefs.h>

#include <src/Interface/bridge.hpp>

namespace Wrapper
{

template <typename Inner>
class base_wrapper : public QObject
{
    W_OBJECT(base_wrapper)

public:
    Inner* get_inner() const
    {
        return inner;
    }

protected:
    explicit base_wrapper()
        : QObject{}
        , inner{new Inner}
    {
        registerToQml();
    }

    void registerToQml() const
    {
        qmlRegisterUncreatableType<Inner>(Inner::uri(), 1, 0, inner->qmlName(), "");
        Interface::bridge::instance().context()->setContextProperty(inner->key(), inner);
    }

    Inner* inner;
};

} // Wrapper

#include <wobjectimpl.h>

W_OBJECT_IMPL(Wrapper::base_wrapper<Inner>, template <typename Inner>)

#endif // BASE_WRAPPER_HPP
