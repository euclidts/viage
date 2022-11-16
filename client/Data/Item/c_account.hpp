#ifndef C_ACCOUNT_HPP
#define C_ACCOUNT_HPP

#include "qdatetime.h"
#include "qnamespace.h"
#include <json/json.h>
#include <Item/account_item.hpp>
#include "c_base_item.hpp"

namespace Data
{
namespace People
{
struct owner_item;
struct contact_item;
}

namespace Places
{
struct habitat_item;
struct exterior_item;
}

struct document_item;

template <typename T>
struct item_list;

using namespace Json;

struct c_account : public account_item
                 , public c_base_item
{
    c_account();

    static const constexpr auto qmlName{"Account"};
    static const constexpr auto uri{"Data"};

    enum roles
    {
        OwnersRole = Qt::UserRole,
        ContactsRole,
        HabitatRole,
        ExteriorRole,
        DocumentsRole,
        StateRole,
        ReceivedRole,
        TransmitedRole,
        ExpertizedRole,
        DecidedRole,
        NotarizedRole,
        PaidRole,
        CreatedRole,
        ModifiedRole,
        AdvisorFirstNameRole,
        AdvisorLastNameRole,
        CompanyRole,
        AcronymRole,
        IdRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    bool update(item_list<People::owner_item>* ol);
    bool update(item_list<People::contact_item>* cl);
    bool update(Places::habitat_item* ht);
    bool update(Places::exterior_item* er);
    bool update(item_list<document_item>* ds);

    Json::Value get(item_list<People::owner_item>* ol) const;
    Json::Value get(item_list<People::contact_item>* cl) const;
    Json::Value get(Places::habitat_item* ht) const;
    Json::Value get(Places::exterior_item* er) const;
    Json::Value get(item_list<document_item>* ds) const;

    void read(const Json::Value & json) { account_item::read(json); };
    void write(Json::Value & json) const { account_item::write(json); };

    bool is_completed() const { return account_item::is_completed(); };

private:
    QDateTime to_QDateTime(const std::string& date, const QString& format = "yyyy-MM-dd hh:mm:ss") const;
    std::string to_date_time(const QDateTime& date, const QString& format = "yyyy-MM-dd hh:mm:ss") const;
    QVariantList to_QVariantList(const Json::Value& json) const;
};

}

#endif // C_ACCOUNT_HPP
