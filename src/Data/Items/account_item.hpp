#ifndef ACCOUNT_ITEM_HPP
#define ACCOUNT_ITEM_HPP

#include <QJsonArray>
#include <QJsonObject>

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

struct account_item
{
    account_item();

    const constexpr char* key() { return "account"; };
    static const constexpr auto qmlName{"Account"};
    static const constexpr auto uri{"Data"};

    QJsonArray owners;
    QJsonArray contacts{};
    // --- Habitat ---
    QJsonObject habitat{};
    // --- Exterior ---
    QJsonObject exterior{};
    // --- Documents ---
    QJsonArray documents{};

    enum states
    {
        Initialized = 0,
        OwnersCompleted = 1,
        ContactsCompleted = 2,
        HabitatCompleted = 4,
        ExteriorCompleted = 8,
        DocumentsCompleted = 16,
        Onboarded = 32,
        Received = 64,
        Expertized = 128,
        Notarized = 256,
        Payed = 512
    };

    states state{Initialized};

    QDate created;
    QDate modified;
    QString advisorFirstName{""};
    QString advisorLastName{""};
    QString company{""};

    QString acronym{""};
    int id{0};

    enum roles
    {
        OwnersRole = Qt::UserRole,
        ContactsRole,
        HabitatRole,
        // --- Exterior ---
        ExteriorRole,
        // --- Documents ---
        DocumentsRole,
        // Account status
        StateRole,
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

    void set(item_list<People::owner_item>* ol);
    void set(item_list<People::contact_item>* cl);
    void set(Places::habitat_item* ht);
    void set(Places::exterior_item* er);
    void set(item_list<document_item>* ds);

    QJsonArray get(item_list<People::owner_item>* ol);
    QJsonArray get(item_list<People::contact_item>* cl) const;
    QJsonObject get(Places::habitat_item* ht);
    QJsonObject get(Places::exterior_item* er);
    QJsonArray get(item_list<document_item>* ds) const;

    void read(const QJsonObject& json);
    void write(QJsonObject &json) const;

    bool is_completed() const;
};

}

#endif // ACCOUNT_ITEM_HPP
