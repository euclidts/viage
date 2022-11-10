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

    const char* key() const override { return "account"; };

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

    bool update(item_list<People::owner_item>* ol);
    bool update(item_list<People::contact_item>* cl);
    bool update(Places::habitat_item* ht);
    bool update(Places::exterior_item* er);
    bool update(item_list<document_item>* ds);

    Value get(item_list<People::owner_item>* ol) const;
    Value get(item_list<People::contact_item>* cl) const;
    Value get(Places::habitat_item* ht) const;
    Value get(Places::exterior_item* er) const;
    Value get(item_list<document_item>* ds) const;

    void read(const Value& json) override;
    void write(Value& json) const override;

    bool is_completed() const override;
};

}

#endif // ACCOUNT_ITEM_HPP
