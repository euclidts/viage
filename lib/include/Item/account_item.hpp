#ifndef ACCOUNT_ITEM_HPP
#define ACCOUNT_ITEM_HPP

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{
using namespace std;
using namespace Json;

struct account_item : virtual public base_data<account_item>
{
    static const constexpr auto key{"account"};
    static const constexpr auto foreign_key{"AccountId"};

    Value owners{};
    Value contacts{};
    Value habitat{};
    bool ppe{false};
    Value exterior{};
    Value documents{};

    enum states
    {
        Initialized = 0,
        OwnersCompleted = 1,
        ContactsCompleted = 2,
        HabitatCompleted = 4,
        ExteriorCompleted = 8,
        DocumentsCompleted = 16,
        Onboarded = 31,
        Received = 32,
        Transmited = 64,
        Expertized = 128,
        Decided = 256,
        Notarized = 512,
        Paid = 1024
    };

    states state{Initialized};
    string receivedDate{""};
    string transmitedDate{""};
    string expertizedDate{""};
    string decidedDate{""};
    string notarizedDate{""};
    string paidDate{""};

    string created{""};
    string modified{""};
    string advisorFirstName{""};
    string advisorLastName{""};
    string company{""};

    string acronym{""};
    int id{0};

    void read(const Value& json) override;
    void write(Value& json) const override;

    bool is_completed() const override;

protected:
    explicit account_item();
};

}

#endif // ACCOUNT_ITEM_HPP
