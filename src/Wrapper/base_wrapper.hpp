#ifndef BASE_WRAPPER_HPP
#define BASE_WRAPPER_HPP

#include <QObject>

#include <wobjectdefs.h>

class QQmlContext;

namespace Service
{
class access;
}

namespace Wrapper
{

template <typename Inner>
class base_wrapper : public QObject
{
    W_OBJECT(base_wrapper)

public:
    Inner* get_inner() const;

protected:
    explicit base_wrapper(Service::access* srv,
                          QQmlContext* context = nullptr);

    void registerToQml(QQmlContext* context) const;

    Inner* inner;
    Service::access* service;
};

}

#include "base_wrapper.cpp"
#endif // BASE_WRAPPER_HPP
