#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"

#include "client_utils.hpp"

namespace client_utils
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

QDateTime to_QDateTime(const std::string& date, const QString& format)
{
    return QDateTime::fromString(QString::fromStdString(date), format);
}

std::string to_date_time(const QDateTime& date, const QString& format)
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

void concatenate(Json::Value &a, const Json::Value& b)
{
    if (!a.isObject() || !b.isObject()) return;

    for (const auto& key : b.getMemberNames())
    {
        if (a[key].isObject())
            concatenate(a[key], b[key]);
        else
            a[key] = b[key];
    }
}

bool is_german()
{
    const auto local{QLocale().language()};

    if (local == QLocale::German
        || local == QLocale::SwissGerman
        || local == QLocale::LowGerman)
        return true;

    return false;
}

}
