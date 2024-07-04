#ifndef INFANT_HPP
#define INFANT_HPP

#include "qnamespace.h"

#include "base_item.hpp"
#include "person.hpp"
#include "senior_citizen.hpp"

namespace Data
{
namespace People
{
struct infant : public base_item<infant>
              , public person
{
    static const constexpr auto key() { return "infant"; }

    enum roles
    {
        // following infant_item roles
        SexRole = Qt::UserRole + 6
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const override;

    bool is_completed() const override;

    senior_citizen::sexes sex;

protected:
    infant();
};

}
}

#endif // INFANT_HPP
