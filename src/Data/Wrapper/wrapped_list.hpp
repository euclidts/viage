#ifndef WRAPPED_LIST_HPP
#define WRAPPED_LIST_HPP

#include <QObject>

#include <wobjectdefs.h>

class QQmlContext;

namespace Service
{
class access;
}

namespace Data
{
namespace Wrapper
{

template <typename Inner>
class wrapped_list : public QObject
{
    W_OBJECT(wrapped_list)

public:
    wrapped_list(Service::access *srv,
                QQmlContext* context);

    Inner* getItem() const;

    void get();

protected:
    wrapped_list(Service::access* srv);
    void registerToQml(QQmlContext* context) const;

    Inner* item;

    Service::access* service;
};

}
}

#include "wrapped_list.cpp"
#endif // WRAPPED_LIST_HPP
