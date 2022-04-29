#pragma once
#include <QQmlContext>

#include <wobjectimpl.h>

#include "wrapped_list.hpp"

#include <access.hpp>
#include <Lists/item_list.hpp>

namespace Data
{
namespace Wrapper
{
W_OBJECT_IMPL(wrapped_list<Inner>, template <typename Inner>)

template <typename Inner>
wrapped_list<Inner>::wrapped_list(Service::access* srv,
                                  QQmlContext* context)
    : QObject{}
    , service(srv)
    , item{new Inner{}}
{
    connect(item,
            &Inner::validate,
            this,
            [=] (int index)
    {
        auto outer = item->item_at(index);

        service->putToKey(item->key(),
                          item->toData(outer.key(), outer.id),
                          [this](const QByteArray& rep) {});
    });

    connect(item,
            &Inner::add,
            this,
            [=] ()
    {
        service->postToKeyAs(item->key(),
                           [this](const QByteArray& rep)
        {
            auto json = QJsonDocument::fromJson(rep).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    item->appendWith(json);
                else
                    qDebug() << "Add error :" << json["errorMessage"].toString();
            }
        });
    });

    if (context)
        registerToQml(context);
}

template<typename Inner>
wrapped_list<Inner>::wrapped_list(Service::access* srv)
    : QObject{}
    , service(srv)
    , item{new Inner{}}
{
}

template<typename Inner>
void wrapped_list<Inner>::registerToQml(QQmlContext* context) const
{
    qmlRegisterUncreatableType<Inner>(item->uri, 1, 0, item->qmlName, "");
    context->setContextProperty(item->key(), item);
}

template<typename Inner>
Inner* wrapped_list<Inner>::getItem() const
{
    return item;
}

template<typename Inner>
void wrapped_list<Inner>::get()
{
    service->getFromKey(item->key(),
                        [this](const QByteArray& bytes)
    { item->read(bytes); });
}

}
}
