#include "c_base_item.hpp"

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

QDate c_base_item::to_QDate(const std::string& date, const QString& format) const
{
    return QDate::fromString(QString::fromStdString(date), format);
}

std::string c_base_item::to_date(const QDate& date, const QString& format) const
{
    return date.toString(format).toStdString();
}

}
