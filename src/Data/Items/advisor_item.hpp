#ifndef ADVISOR_ITEM_HPP
#define ADVISOR_ITEM_HPP

#include "person_item.hpp"
#include "address_item.hpp"

namespace Data
{
namespace People
{
struct advisor_item : public person_item
                    , public Places::address_item
{
    advisor_item();

    const constexpr char* key() { return "advisor"; };
    static const constexpr auto qmlName{"Advisor"};

    enum level
    {
        Vendor = 0,
        Manager,
        Director,
        Administrator
    };

    QString company{""};
    int clearance{Vendor};
    int team{1};
    QString beneficiary{""};
    QString iban{""};
    QString bic{""};

    enum roles
    {
        // following person_items roles
        CompanyRole = Qt::UserRole + 4,
        ClearanceRole,
        TeamNumberRole,
        BeneficiaryRole,
        // gap left for address_item roles
        IbanRole = Qt::UserRole + 12,
        BicRole = Qt::UserRole + 13
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;
};

}
}

#endif // ADVISOR_ITEM_HPP
