#ifndef RENT_ITEM_H
#define RENT_ITEM_H

#include <QJsonArray>
#include <QJsonObject>

#include <wobjectdefs.h>

#include "base_item.hpp"

namespace Data
{
class rent_item : public base_item
{
W_OBJECT(rent_item)

public:
    explicit rent_item(QObject* parent = nullptr);

    const constexpr char* key() override { return "rent"; };
    static const constexpr auto qmlName{"RentItem"};
    static const constexpr auto uri{"Data"};

    void clear() override;
    W_SLOT(clear)

    void calculate()
    W_SIGNAL(calculate)

    void expectencyChanged()
    W_SIGNAL(expectencyChanged)

    double getExpectency() const;
    void setExpectency(double newExpectency);
    void resetExpectency();

    W_PROPERTY(double, expectency READ getExpectency WRITE setExpectency NOTIFY expectencyChanged);

private:
    double expectency{0};
};

}

#endif // RENT_ITEM_H
