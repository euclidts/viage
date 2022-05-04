#ifndef SENIOR_CITIZEN_ITEM_H
#define SENIOR_CITIZEN_ITEM_H

#include <QJsonObject>

namespace Data
{
namespace People
{

#define AGE_MIN 65
#define AGE_MAX 120

struct senior_citizen_item
{
    senior_citizen_item();

    const constexpr char* key() { return "seniorCitizen"; };
    static const constexpr auto qmlName{"SeniorCitizen"};
    static const constexpr auto uri{"People"};

    QDate birthDay;

    enum sexes
    {
        M = 0,
        F
    };

    sexes sex{sexes(M)};

    enum roles
    {
        BirthDayRole = Qt::UserRole,
        SexRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);
};

}
}

#endif // SENIOR_CITIZEN_ITEM_H
