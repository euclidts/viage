#include <cmath>
#include <Item/rent_item.hpp>

namespace Data
{

#define INTEREST 0.0425
#define I -0.0225
#define V 1/(1 + I)

rent_item::rent_item()
    : base_data{}
{
}

int rent_item::floor_to(double number, int multiple) const
{
    return std::floor((number + multiple / 2) / multiple) * multiple;
}

void rent_item::from_expectency(double expectency)
{
    using namespace std;

    pva = floor_to(marketPrice / pow(1 + INTEREST, expectency), 1000);
    dab = marketPrice - pva;

    double ae{0};
    if (V == 1)
        ae = expectency;
    else
    {
        double ve{1 - pow(V, expectency)};
        ae = ve / (1 - V) - 11.f / 24.f * ve;
    }

    rva = 12 * monthly * ae;
    bou = marketPrice - dab - rva;
    pva = dab + bou;
}

//int rent_item::getDam() const
//{
//    return dam;
//}

//void rent_item::setDam(int newDam)
//{
//    if (dam == newDam)
//        return;
//    dam = newDam;
//    emit damChanged();
//}

}
