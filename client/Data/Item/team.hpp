#ifndef TEAM_HPP
#define TEAM_HPP

#include "qnamespace.h"

#include "base_item.hpp"

namespace Data
{
struct team final : base_item<team>
{
    team();

    static const constexpr auto key() { return "Team"; }
    static const constexpr auto qmlName() { return "Team"; }
    static const constexpr auto uri() { return "Data"; }

    enum roles
    {
        IdRole = Qt::UserRole,
        CaptionRole,
        HasUsersRole
    };

    static QHash<int , QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const override;

    bool is_completed() const override;

    int id;

private:
    QString caption;
    bool has_users;
};

}

#endif // TEAM_HPP
