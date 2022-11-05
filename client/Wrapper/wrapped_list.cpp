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
        QJsonObject obj{};
        auto item{this->inner->item_at_id(id)};
        item.write(obj);

        QJsonObject json{{ item.key(), obj }};

        this->mng->putToKey(this->inner->key(),
                            QJsonDocument{json}.toJson(),
                            [this](const QJsonObject& rep)
        {},
        "Validate error");
    });

    this->connect(this->inner,
                  &Inner::add,
                  this,
                  [this] ()
    {
        this->mng->postToKey(this->inner->key(),
                             QByteArray{},
                             [this](const QJsonObject& rep)
        { this->inner->appendWith(rep); },
        "Add error");
    });

    this->connect(this->inner,
                  &Inner::addWith,
                  this,
                  [this] (const QJsonObject& obj)
    {
        QJsonDocument data{obj};

        this->mng->postToKey(this->inner->key(),
                                 data.toJson(),
                                 [this, obj](const QJsonObject& res)
        {
            auto map{res.toVariantMap()};
            map.insert(obj.toVariantMap());

            const auto json{QJsonObject::fromVariantMap(map)};
            this->inner->appendWith(json);
        },
        "addWith error");
    });

    connectRemove();
}

template<typename Inner>
void wrapped_list<Inner>::connectRemove() const
{
    this->connect(this->inner,
                  &Inner::remove,
                  this,
                  [this] (int id)
    {
        this->inner->erase(id);

        const QJsonObject json{{"id", id}};
        this->mng->deleteToKey(this->inner->key(),
                               QJsonDocument{json}.toJson(),
                               [this, id](const QJsonObject& rep) {},
        "Remove Error");
    });
}
}
