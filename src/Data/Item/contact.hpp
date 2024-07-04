#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <list.hpp>
#include "infant.hpp"

namespace Data
{
namespace People
{
struct contact final : public base_item<contact>
                     , public infant
{
    contact();

    static const constexpr auto key() { return "contact"; }
    static const constexpr auto qmlName() { return "Contact"; }

    enum roles
    {
        // following infant_items roles
        IsInfantRole = Qt::UserRole + 5
    };

    static QHash<int, QByteArray> roleNames();

    QVariant data(int role) const;
    void setData(const QVariant& value, int role);

    void read(const QJsonObject& json);
    void write(QJsonObject& json) const override;

    bool is_completed() const override;

private:
    bool isInfant;
};
}

template<>
inline bool list<People::contact>::is_completed() const
{
    return is_empty_completed();
}
}

#endif // CONTACT_HPP
