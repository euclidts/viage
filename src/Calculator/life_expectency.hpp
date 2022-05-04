#ifndef EXPECTENCY
#define EXPECTENCY

#include <QDate>

#include <Items/senior_citizen_item.hpp>

namespace Data
{
template <typename T>
class simple_item_list;
}

namespace Calculator
{

class life_expectency
{
public:
    explicit life_expectency(
            Data::simple_item_list<Data::People::senior_citizen_item>*
            senior_citizens);

    double get_expectency();

private:
    Data::simple_item_list<Data::People::senior_citizen_item>* seniors;

    struct data
    {
        data() {};
        data(const Data::People::senior_citizen_item& senior)
            : sex{senior.sex}
            , thousand_bDAy{senior.birthDay.year() * 1000}
            , age{senior.birthDay.daysTo(QDate::currentDate()) / 365.25}
            , age_trunc{std::trunc(age)}
            , age_diff{age - std::round(age)}
        {}
        Data::People::senior_citizen_item::sexes sex{Data::People::senior_citizen_item::M};
        int thousand_bDAy{0};
        double age{0};
        double age_trunc{0};
        double age_diff{0};
    };

    std::map<int, std::array<double, 2>> mortality{};
    int mortality_offset{0};

    void readMortality(const QString& path);
    double get_mortality();

    double get_pers(const data& d, int index, int plus = 0);
    double get_qx(const data& d, int index);
};

}

#endif // EXPECTENCY
