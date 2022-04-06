#ifndef CACHED_LIST_HPP
#define CACHED_LIST_HPP

#include <QObject>

#include <wobjectdefs.h>

class QQmlContext;

namespace Service
{
class access;
}

namespace Data
{
namespace Cache
{
class cache;

template <typename Inner>
class cached_list : public QObject
{
    W_OBJECT(cached_list)

public:
    cached_list(cache* storage,
                Service::access *srv,
                QQmlContext* context = nullptr);

    Inner* getItem() const;

    void get();

protected:
    cached_list(Service::access* srv);
    void registerToQml(QQmlContext* context) const;

    Inner* item;

    Service::access* service;
};

}
}

#include "cached_list.cpp"
#endif // CACHED_LIST_HPP
