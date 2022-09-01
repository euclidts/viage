#ifndef USER_ITEM_HPP
#define USER_ITEM_HPP

#include "person_item.hpp"
#include "address_item.hpp"

namespace Data
{
namespace People
{
struct user_item : public person_item
                 , public Places::address_item
{
    user_item();

    const constexpr char* key() { return "user"; };
    static const constexpr auto qmlName{"User"};

    enum clearances
    {
        None = 0,
        Vendor,
        Manager,
        Director,
        Administrator
    };

    QString company{""};
    int company_id{0};
    clearances clearance{Vendor};
    QString team{""};
    int team_id{0};
    QString beneficiary{""};
    QString iban{""};
    QString bic{""};
    bool isLocked{false};

    enum roles
    {
        // following person_items roles
        CompanyRole = Qt::UserRole + 5,
        ClearanceRole,
        TeamNameRole,
        BeneficiaryRole,
        // gap left for address_item roles
        IbanRole = Qt::UserRole + 14,
        BicRole,
        CompanyIdRole,
        TeamIdRole,
        LockedRole,
        CompletedRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    bool is_completed() const;
};

}
}

#endif // USER_ITEM_HPP
