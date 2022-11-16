#include "c_base_item.hpp"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

namespace Data
{

QString c_base_item::to_QString(const std::string& str) const
{
    return QString::fromStdString(str);
}

std::string c_base_item::to_string(const QString& str) const
{
    return str.toStdString();
}

std::string c_base_item::to_string(const QVariant &var) const
{
    return var.toString().toStdString();
}

QDate c_base_item::to_QDate(const std::string& date, const QString& format) const
{
    return QDate::fromString(QString::fromStdString(date), format);
}

std::string c_base_item::to_date(const QDate& date, const QString& format) const
{
    return date.toString(format).toStdString();
}

QJsonArray c_base_item::to_QJsonArray(const Json::Value &json) const
{
    return to_QJsonDoc(json).array();
}

QJsonObject c_base_item::to_QJsonObject(const Json::Value &json) const
{
    return to_QJsonDoc(json).object();
}

QJsonDocument c_base_item::to_QJsonDoc(const Json::Value &json) const
{
    Json::StreamWriterBuilder builder;
    const std::string json_str = Json::writeString(builder, json);

    return QJsonDocument::fromJson(json_str.c_str());
}

}
