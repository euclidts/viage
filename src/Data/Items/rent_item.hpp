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

    void from_expectency(double expectency);

    void calculate()
    W_SIGNAL(calculate)

    void clear() override;
    W_SLOT(clear)

    void marketPriceChanged()
    W_SIGNAL(marketPriceChanged)
    void monthlyChanged()
    W_SIGNAL(monthlyChanged)
    void rvaChanged()
    W_SIGNAL(rvaChanged)
    void bouChanged()
    W_SIGNAL(bouChanged)
    void dabChanged()
    W_SIGNAL(dabChanged)
    void estimationChanged()
    W_SIGNAL(estimationChanged)
//    void damChanged()
//    W_SIGNAL(damChanged)

    int getmarketPrice() const;
    void setmarketPrice(int newmarketPrice);
    int getMonthly() const;
    void setMonthly(int newMonthly);
    int getRva() const;
    void setRva(int newRva);
    int getBou() const;
    void setBou(int newBou);
    int getDab() const;
    void setDab(int newDab);
    int getEstimation() const;
    void setEstimation(int newEstimation);
//    int getDam() const;
//    void setDam(int newDam);

    W_PROPERTY(int, marketPrice READ getmarketPrice WRITE setmarketPrice NOTIFY marketPriceChanged)
    W_PROPERTY(int, monthly READ getMonthly WRITE setMonthly NOTIFY monthlyChanged)
    W_PROPERTY(int, rva READ getRva NOTIFY rvaChanged)
    W_PROPERTY(int, bou READ getBou NOTIFY bouChanged)
    W_PROPERTY(int, dab READ getDab NOTIFY dabChanged)
    W_PROPERTY(int, estimation READ getEstimation NOTIFY estimationChanged)
//    W_PROPERTY(int, dam READ getDam WRITE setDam NOTIFY damChanged)

private:
    int marketPrice{1500000};
    int monthly{0};

    int rva{0};
    int bou{0};
    int dab{0};
    int estimation{0};
    //    int dam{0};

    int floor_to(double number, int multiple) const;
};

}

#endif // RENT_ITEM_H
