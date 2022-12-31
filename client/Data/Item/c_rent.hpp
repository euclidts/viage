#ifndef C_RENT_HPP
#define C_RENT_HPP

#include <wobjectdefs.h>
#include "c_base_data.hpp"
#include <Item/rent_item.hpp>

namespace Data
{
class c_rent : public c_base_data
             , public rent_item
{
W_OBJECT(c_rent)

public:
    explicit c_rent(QObject* parent = nullptr);

    static const constexpr auto qmlName{"RentItem"};
    static const constexpr auto uri{"Data"};

    void read(const Json::Value& json) override;
    void write(Json::Value& json) const override;

    void clear() override;
    W_SLOT(clear)

    void from_expectency(double expectency);

    void calculate()
    W_SIGNAL(calculate)

    void writeToFile()
    W_SIGNAL(writeToFile)

    void birthDayChanged()
    W_SIGNAL(birthDayChanged)
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
    void pvaChanged()
    W_SIGNAL(pvaChanged)
//    void damChanged()
//    W_SIGNAL(damChanged)

    const QDate getBirthDay() const;
    void setBirthDay(const QDate &newBirthDay);
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
    int getPva() const;
    void setPva(int newPva);
//    int getDam() const;
//    void setDam(int newDam);

    W_PROPERTY(QDate, birthDay READ getBirthDay WRITE setBirthDay NOTIFY birthDayChanged)
    W_PROPERTY(int, marketPrice READ getmarketPrice WRITE setmarketPrice NOTIFY marketPriceChanged)
    W_PROPERTY(int, monthly READ getMonthly WRITE setMonthly NOTIFY monthlyChanged)
    W_PROPERTY(int, rva READ getRva NOTIFY rvaChanged)
    W_PROPERTY(int, bou READ getBou NOTIFY bouChanged)
    W_PROPERTY(int, dab READ getDab NOTIFY dabChanged)
    W_PROPERTY(int, pva READ getPva NOTIFY pvaChanged)
//    W_PROPERTY(int, dam READ getDam WRITE setDam NOTIFY damChanged)

    int floor_to(double number, int multiple) const;
};

}

#endif // RENT_ITEM_H
