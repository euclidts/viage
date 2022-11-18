#ifndef ACCOUNT_ITEM_HPP
#define ACCOUNT_ITEM_HPP

#include <json/json.h>
#include <base_data.hpp>

namespace Data
{

namespace People
{
struct owner_item;
struct contact_item;
}

namespace Places
{
struct habitat_item;
struct exterior_item;
}

struct document_item;

template <typename T>
struct item_list;

using namespace std;
using namespace Json;

struct account_item : virtual public base_data
{
    explicit account_item();

    static const constexpr char* key() { return "account"; };

    Value owners{};
    Value contacts{};
    Value habitat{};
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
    string receivedDate{};
    string transmitedDate{};
    string expertizedDate{};
    string decidedDate{};
    string notarizedDate{};
    string paidDate{};

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
};

}

#endif // ACCOUNT_ITEM_HPP
