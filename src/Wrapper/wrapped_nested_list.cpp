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
                                 [this](const QByteArray& res)
        {
            const auto json = QJsonDocument::fromJson(res).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    this->inner->appendWith(json["id"].toInt());
                else
                    qDebug() << "addIn error :" << json["errorMessage"].toString();
            };
        });
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
                                 [this, obj](const QByteArray& res)
        {
            auto json = QJsonDocument::fromJson(res).object();
            auto map{json.toVariantMap()};

            map.insert(obj.toVariantMap());

            json = QJsonObject::fromVariantMap(map);

            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    this->inner->appendWith(json);
                else
                    qDebug() << "addInWith error :" << json["errorMessage"].toString();
            };
        });
    });
}

}
