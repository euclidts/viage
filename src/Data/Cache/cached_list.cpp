#pragma once
#include <QQmlContext>

#include <wobjectimpl.h>

#include "cached_list.hpp"

#include "cache.hpp"
#include <access.hpp>
#include <Lists/item_list.hpp>

namespace Data
{
namespace Cache
{
W_OBJECT_IMPL(cached_list<Inner>, template <typename Inner>)

template <typename Inner>
cached_list<Inner>::cached_list(cache* storage,
                                Service::access* srv,
                                QQmlContext* context)
    : QObject{}
    , service(srv)
    , item{new Inner{}}
{
//    connect(item,
//            &Inner::validate,
//            this,
//            [=] (int index)
//    {
//        QJsonObject jsonElement{};
//        item->item_at(index).write(jsonElement);
//        storage->update(index, jsonElement, item->key());
//    });

    connect(this->item,
            &Inner::validate,
            this,
            [=] (int index)
    {
        auto outer = item->item_at(index);

        service->putToKey(item->key(),
                          item->toData(outer.key(), outer.id),
                          [this](const QByteArray& rep)
        { qDebug() << rep; });
    });

    connect(item,
            &Inner::add,
            this,
            [=] ()
    {
        service->postToKey(item->key(),
                           QByteArray(),
                           [this](const QByteArray& rep)
        {
            const auto json = QJsonDocument::fromJson(rep).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    item->appendWith(json);
                else
                    qDebug() << json["errorMessage"].toString();
            }
        });
    });

    if (context)
        registerToQml(context);
}

template<typename Inner>
cached_list<Inner>::cached_list(Service::access* srv)
    : QObject{}
    , service(srv)
    , item{new Inner{}}
{
}

template<typename Inner>
void cached_list<Inner>::registerToQml(QQmlContext* context) const
{
    qmlRegisterUncreatableType<Inner>(item->uri, 1, 0, item->qmlName, "");
    context->setContextProperty(item->key(), item);
}

template<typename Inner>
Inner* cached_list<Inner>::getItem() const
{
    return item;
}

template<typename Inner>
void cached_list<Inner>::get()
{
    service->getFromKey(item->key(),
                        [this](const QByteArray& bytes)
    { item->read(bytes); });
}

}
}
