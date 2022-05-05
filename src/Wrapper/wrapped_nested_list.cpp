#pragma once

#include "wrapped_nested_list.hpp"

namespace Data
{
namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Service::access* srv,
                                                       item_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{srv, context}
{
    this->makeConnections(parentList);

    this->connect(this->inner,
                  &Inner::addIn,
                  this,
                  [=] (int id)
    {
        QJsonObject json{ {"id", id} };
        QJsonDocument data{json};

        this->service->postToKey(this->inner->key(),
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

        this->service->postToKey(this->makeKey(parentList).c_str(),
                                 data.toJson(),
                                 [this, &obj](const QByteArray& res)
        {
            const auto json = QJsonDocument::fromJson(res).object();
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
}
