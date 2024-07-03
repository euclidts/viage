#ifndef OWNER_HPP
#define OWNER_HPP

#include "qnamespace.h"
#include "infant.hpp"
#include "address.hpp"

namespace Data
{
namespace People
{
struct owner final : public base_item<owner>
                   , public infant
{
    owner();

    static const constexpr auto key() { return "owner"; }
    static const constexpr auto qmlName() { return "Owner"; }

    enum civilStates
    {
        None = 0,
        Single,
        Maried,
        Registered,
        Separated,
        Divorced,
        Disolved,
        Widow
    };

    enum roles
    {
        // following infant_items roles
        BirthDayRole = Qt::UserRole + 7,
        CivilStatusRole,
        AVSRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const override;

    bool is_completed() const override;

    civilStates civilStatus;

    Places::address address;

protected:
    QDate birthDay;
    QString avs;
};
}
}

#endif // OWNER_HPP
