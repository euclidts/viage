#pragma once
#include <QQmlContext>

#include "wrapped_list.hpp"

#include <netManager.hpp>
#include <Lists/item_list.hpp>

namespace Wrapper
{
template <typename Inner>
wrapped_list<Inner>::wrapped_list(Interface::netManager* manager,
                                  QQmlContext* context)
    : base_wrapper<Inner>{manager, context}
{
}

template<typename Inner>
void wrapped_list<Inner>::get() const
{
    this->mng->getFromKey(this->inner->key(),
                              [this](const QByteArray& bytes)
    { this->inner->read(bytes); });
}

template<typename Inner>
void wrapped_list<Inner>::makeConnections() const
{
    this->connect(this->inner,
                  &Inner::validate,
                  this,
                  [this] (int id)
    {
        auto item = this->inner->item_at_id(id);

        this->mng->putToKey(this->inner->key(),
                                this->inner->toData(item.key(), id),
                                [this](const QByteArray& rep)
        {
            qDebug() << rep;
        });
    });

    this->connect(this->inner,
                  &Inner::add,
                  this,
                  [this] ()
    {
        this->mng->postToKey(this->inner->key(),
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
