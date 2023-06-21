#pragma once
#include "wrapped_nested_list.hpp"
#include "qjsondocument.h"

namespace Wrapper
{
template <typename Inner, typename Outer>
wrapped_nested_list<Inner, Outer>::wrapped_nested_list(Data::c_list<Outer>* parentList,
                                                       QQmlContext* context)
    : wrapped_nested_item<Inner, Outer>{context}
    , key{this->makeKey(parentList)}
{
    this->inner->complitionChecks();

    this->makeConnections(parentList);
    this->connectRemove();

    this->connect(this->inner,
                  &Inner::addIn,
                  this,
                  [this] (int id)
                  { add_in_with(id); });

    this->connect(this->inner,
                  &Inner::addInWith,
                  this,
                  [this, parentList] (int id, const QJsonObject& obj)
                  { add_in_with(id, obj, parentList); });
}

template<typename Inner, typename Outer>
void wrapped_nested_list<Inner, Outer>::add_in_with(int id,
                                                    const QJsonObject& obj,
                                                    Data::c_list<Outer>* parentList)
{
    auto json{obj};
    Json::Value val{Utils::to_Json(obj)};

    json[Outer::foreign_key] = id;
    QJsonDocument doc{json};
    QByteArray data{doc.toJson(QJsonDocument::Compact)};

    Interface::netManager::instance().postToKey(key.c_str(),
        data,
        [this, val, parentList, id](const Json::Value& res)
    {
        Json::Value concat{val};
        Utils::concatenate(concat, res);
        this->inner->appendWith(concat);

        if (parentList)
        {
            Outer outer{parentList->item_at_id(id)};
            outer.update(this->inner);
            parentList->setItemAtId(id, outer);
        }
    },
    "addInWith error");
}

}
