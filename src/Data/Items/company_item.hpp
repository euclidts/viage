#ifndef COMPANY_ITEM_HPP
#define COMPANY_ITEM_HPP

#include <QJsonArray>

namespace Data
{

template <typename T>
struct item_list;

struct team_item;

struct company_item
{
    company_item();

    const constexpr char* key() { return "company"; };
    static const constexpr auto qmlName{"Company"};
    static const constexpr auto uri{"Data"};

    int id{0};
    QString name{};
    QJsonArray teams{};

    enum roles
    {
        IdRole = Qt::UserRole,
        NameRole,
        TeamsRole
    };

    static QHash<int , QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void set(item_list<team_item>* ti);
    QJsonArray get(item_list<team_item>* ti) const;

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const;

    bool is_completed() const;
};

}

#endif // COMPANY_ITEM_HPP
