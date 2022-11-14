#ifndef C_BASE_ITEM_HPP
#define C_BASE_ITEM_HPP

#include "qdatetime.h"
#include <qstring.h>

namespace Data
{
struct c_base_item
{
protected:

    QString to_QString(const std::string& str) const;

    std::string to_string(const QString &str) const;

    QDate to_QDate(const std::string& date, const QString& format = "yyyy-MM-dd") const;

    std::string to_date(const QDate& date, const QString& format = "dd.MM.yyyy") const;
};
}

#endif // BASE_ITEM_HPP
