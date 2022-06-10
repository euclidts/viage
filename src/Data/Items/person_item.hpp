#ifndef PERSON_ITEM_HPP
#define PERSON_ITEM_HPP

#include <QJsonObject>

namespace Data
{
namespace People
{
struct person_item
{
    static const constexpr auto uri{"People"};

    int id{0};
    QString firstName{""};
    QString lastName{""};
    QString phone{""};
    QString eMail{""};

    enum roles
    {
        IdRole = Qt::UserRole,
        FirstNameRole,
        LastNameRole,
        PhoneRole,
        EmailRole
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject &json) const;

protected:
    person_item();

    bool is_completed() const;
};

}
}

#endif // PERSON_ITEM_HPP
