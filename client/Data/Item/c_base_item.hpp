#ifndef C_BASE_ITEM_HPP
#define C_BASE_ITEM_HPP

#include "qdatetime.h"
#include <json/json.h>
#include <qstring.h>

namespace Data
{
struct c_base_item
{
protected:
    QString to_QString(const std::string& str) const;
    std::string to_string(const QString &str) const;
    std::string to_string(const QVariant &var) const;

    QDate to_QDate(const std::string& date, const QString& format = "yyyy-MM-dd") const;
    std::string to_date(const QDate& date, const QString& format = "dd.MM.yyyy") const;

    QJsonArray to_QJsonArray(const Json::Value& json) const;
    QJsonObject to_QJsonObject(const Json::Value& json) const;
    QJsonDocument to_QJsonDoc(const Json::Value& json) const;
};
}

#endif // BASE_ITEM_HPP
