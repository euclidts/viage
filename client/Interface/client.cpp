#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

#include "client.hpp"

namespace Client
{
QString to_QString(const std::string& str)
{
    return QString::fromStdString(str);
}

std::string to_string(const QString& str)
{
    return str.toStdString();
}

std::string to_string(const QVariant &var)
{
    return var.toString().toStdString();
}

QDate to_QDate(const std::string& date, const QString& format)
{
    return QDate::fromString(QString::fromStdString(date), format);
}

std::string to_date(const QDate& date, const QString& format)
{
    return date.toString(format).toStdString();
}

QJsonArray to_QJsonArray(const Json::Value &json)
{
    return to_QJsonDoc(json).array();
}

QJsonObject to_QJsonObject(const Json::Value &json)
{
    return to_QJsonDoc(json).object();
}

QJsonDocument to_QJsonDoc(const Json::Value &json)
{
    Json::StreamWriterBuilder builder;
    const std::string json_str = Json::writeString(builder, json);

    return QJsonDocument::fromJson(json_str.c_str());
}

Json::Value to_Json(const std::string& str)
{
    Json::Value json;
    Json::Reader reader;
    reader.parse(str, json);
    return json;
}

Json::Value to_Json(const QByteArray& bytes)
{
    return to_Json(bytes.toStdString());
}

Json::Value to_Json(const QJsonObject& obj)
{
    QJsonDocument doc{obj};
    QByteArray bytes{doc.toJson(QJsonDocument::Compact)};
    return to_Json(bytes);
}

QByteArray to_QByteArray(const Json::Value &json)
{
    Json::StreamWriterBuilder builder;
    const std::string str = Json::writeString(builder, json);
    return QByteArray::fromStdString(str);
}


}
