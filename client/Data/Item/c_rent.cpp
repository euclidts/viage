#include "qdatetime.h"

#include <wobjectimpl.h>

#include "c_rent.hpp"
#include <utils.hpp>

using namespace Utils;

namespace Data
{

#define INTEREST 0.0425
#define I -0.0225
#define V 1/(1 + I)

W_OBJECT_IMPL(c_rent)

c_rent::c_rent(QObject *parent)
    : c_base_data{parent}
    , rent_item{}
{
    birthDay = to_date(QDate::currentDate());
}

void c_rent::read(const Json::Value &json)
{
    int prev_bou{bou};
    int prev_dab{dab};

    rent_item::read(json);

    if (prev_bou != bou)
        emit bouChanged();

    if (prev_dab != dab)
        emit dabChanged();

    emit loaded();
}

void c_rent::write(Json::Value &json) const
{
    rent_item::write(json);
}

void c_rent::clear()
{
    setBirthDay(QDate::currentDate());
    setmarketPrice(1500000);
    setMonthly(0);
    setBou(0);
    setRva(0);
    setDab(0);
    setPva(0);
//    setDam{0};
}

int c_rent::floor_to(double number, int multiple) const
{
    return std::floor((number + multiple / 2) / multiple) * multiple;
}

void c_rent::from_expectency(double expectency)
{
    using namespace std;

    int pva = floor_to(marketPrice / pow(1 + INTEREST, expectency), 1000);
    setDab(marketPrice - pva);

    double ae{0};
    if (V == 1)
        ae = expectency;
    else
    {
        double ve{1 - pow(V, expectency)};
        ae = ve / (1 - V) - 11.f / 24.f * ve;
    }

    setRva(12 * monthly * ae);
    setBou(marketPrice - dab - rva);
    setPva(dab + bou);
}

int c_rent::getmarketPrice() const
{
    return marketPrice;
}

void c_rent::setmarketPrice(int newmarketPrice)
{
    if (marketPrice == newmarketPrice)
        return;
    marketPrice = newmarketPrice;
    emit marketPriceChanged();
}

int c_rent::getMonthly() const
{
    return monthly;
}

void c_rent::setMonthly(int newMonthly)
{
    if (monthly == newMonthly)
        return;
    monthly = newMonthly;
    emit monthlyChanged();
}

int c_rent::getRva() const
{
    return rva;
}

void c_rent::setRva(int newRva)
{
    if (rva == newRva)
        return;
    rva = newRva;
    emit rvaChanged();
}

int c_rent::getBou() const
{
    return bou;
}

void c_rent::setBou(int newBou)
{
    if (bou == newBou)
        return;
    bou = newBou;
    emit bouChanged();}

int c_rent::getDab() const
{
    return dab;
}

void c_rent::setDab(int newDab)
{
    if (dab == newDab)
        return;
    dab = newDab;
    emit dabChanged();
}

int c_rent::getPva() const
{
    return pva;
}

void c_rent::setPva(int newPva)
{
    if (pva == newPva)
        return;
    pva = newPva;
    emit pvaChanged();
}

const QDate c_rent::getBirthDay() const
{
    return to_QDate(birthDay);
}

void c_rent::setBirthDay(const QDate& newBirthDay)
{
    if (to_QDate(birthDay) == newBirthDay)
        return;
    birthDay = to_date(newBirthDay);
    emit birthDayChanged();
}

//int c_rent::getDam() const
//{
//    return dam;
//}

//void c_rent::setDam(int newDam)
//{
//    if (dam == newDam)
//        return;
//    dam = newDam;
//    emit damChanged();
//}

}
