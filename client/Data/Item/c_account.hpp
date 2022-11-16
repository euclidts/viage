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
struct c_owner;
struct c_contact;
}

namespace Places
{
struct c_habitat;
struct c_exterior;
}

struct c_document;

template <typename T>
struct c_list;

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
//        ContactsRole,
        HabitatRole,
//        ExteriorRole,
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

    bool update(c_list<People::c_owner>* ol);
    bool update(c_list<People::c_contact>* cl);
    bool update(Places::c_habitat* ht);
    bool update(Places::c_exterior* er);
    bool update(c_list<c_document>* ds);

    Json::Value get(c_list<People::c_owner>* ol) const { return account_item::get(ol); };
    Json::Value get(c_list<People::c_contact>* cl) const { return account_item::get(cl); };
    Json::Value get(Places::c_habitat* ht) const { return account_item::get(ht); };
    Json::Value get(Places::c_exterior* er) const { return account_item::get(er); };
    Json::Value get(c_list<c_document>* ds) const { return account_item::get(ds); };

    void read(const Json::Value & json) { account_item::read(json); };
    void write(Json::Value & json) const { account_item::write(json); };

    bool is_completed() const { return account_item::is_completed(); };

private:
    QDateTime to_QDateTime(const std::string& date, const QString& format = "yyyy-MM-dd hh:mm:ss") const;
    std::string to_date_time(const QDateTime& date, const QString& format = "yyyy-MM-dd hh:mm:ss") const;
};

}

#endif // C_ACCOUNT_HPP
