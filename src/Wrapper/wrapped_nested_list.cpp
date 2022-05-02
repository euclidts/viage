#pragma once
#include <wobjectimpl.h>

#include "wrapped_nested_list.hpp"

namespace Data
{
namespace Wrapper
{
W_OBJECT_IMPL((wrapped_nested_list<Inner, Outer>), template <typename Inner, typename Outer>)

template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Service::access* srv,
                                                       item_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{srv,
                                        parentList,
                                        context}
{
    this->connect(this->item,
                  &Inner::addIn,
                  this,
                  [=] (int id)
    {
        QJsonObject json{ {"id", id} };
        QJsonDocument data{json};

        this->service->postToKey(this->item->key(),
                                 data.toJson(),
                                 [this](const QByteArray& res)
        {
            const auto json = QJsonDocument::fromJson(res).object();
            if (json.contains("success") && json["success"].isBool())
            {
                if (json["success"].toBool())
                    this->item->appendWith(json["id"].toInt());
                else
                    qDebug() << "addIn error :" << json["errorMessage"].toString();
            };
        });
    });

    this->connect(this->item,
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
                    this->item->appendWith(json);
                else
                    qDebug() << "addInWith error :" << json["errorMessage"].toString();
            };
        });
    });
}

}
}
