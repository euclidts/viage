#pragma once
#include <QQmlContext>

#include "wrapped_list.hpp"

#include <access.hpp>
#include <Lists/item_list.hpp>

namespace Data
{
namespace Wrapper
{
template <typename Inner>
wrapped_list<Inner>::wrapped_list(Service::access* srv,
                                  QQmlContext* context)
    : base_wrapper<Inner>{srv, context}
{
}

template<typename Inner>
void wrapped_list<Inner>::get() const
{
    this->service->getFromKey(this->inner->key(),
                              [this](const QByteArray& bytes)
    { this->inner->read(bytes); });
}

template<typename Inner>
void wrapped_list<Inner>::makeConnections() const
{
    this->connect(this->inner,
                  &Inner::validate,
                  this,
                  [=] (int id)
    {
        auto item = this->inner->item_at_id(id);

        this->service->putToKey(this->inner->key(),
                                this->inner->toData(item.key(), id),
                                [this](const QByteArray& rep) {});
    });

    this->connect(this->inner,
                  &Inner::add,
                  this,
                  [=] ()
    {
        this->service->postToKey(this->inner->key(),
                                 QByteArray{},
                                 [this](const QByteArray& rep)
        {
            auto json = QJsonDocument::fromJson(rep).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    this->inner->appendWith(json);
                else
                    qDebug() << "Add error :" << json["errorMessage"].toString();
            }
        });
    });
}

}
}
