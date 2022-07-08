#pragma once

#include "wrapped_nested_list.hpp"

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Interface::netManager* manager,
                                                       Data::item_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{manager, context}
{
    this->inner->complitionChecks();

    this->makeConnections(parentList);
    this->connectRemove();

    this->connect(this->inner,
                  &Inner::addIn,
                  this,
                  [=] (int id)
    {
        QJsonObject json{ {"id", id} };
        QJsonDocument data{json};

        this->mng->postToKey(this->inner->key(),
                                 data.toJson(),
                                 [this](const QJsonObject& res)
        { this->inner->appendWith(res["id"].toInt()); },
        "addIn error");
    });

    this->connect(this->inner,
                  &Inner::addInWith,
                  this,
                  [=] (int id, const QJsonObject& obj)
    {
        QJsonObject json{obj};
        json["id"] = id;
        QJsonDocument data{json};

        this->mng->postToKey(this->makeKey(parentList).c_str(),
                                 data.toJson(),
                                 [this, obj](const QJsonObject& res)
        {
            auto map{res.toVariantMap()};
            map.insert(obj.toVariantMap());

            const auto json{QJsonObject::fromVariantMap(map)};
            this->inner->appendWith(json);
        },
        "addInWith error");
    });
}

}
