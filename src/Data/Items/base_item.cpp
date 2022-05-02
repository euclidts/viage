#include "base_item.hpp"
#include "qjsondocument.h"
#include "qjsonobject.h"

namespace Data
{

base_item::base_item(QObject* parent)
    : base_data{parent}
{
    clear();
}

void base_item::writeWithKey(QJsonObject &json)
{
    QJsonObject obj{};
    write(obj);

    json[key()] = obj;
}
}
