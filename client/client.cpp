#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "client.hpp"
#include <bridge.hpp>
#include <document_filter_model.hpp>
#include <user_filter_model.hpp>
#include <wrapped_calculator.hpp>
#include <wrapped_nested_list.hpp>
#include <account_filter_model.hpp>

#include <Data/Item/c_contact.hpp>
#include <Data/Item/c_habitat.hpp>
#include <Data/Item/c_exterior.hpp>
#include <Data/Item/c_document.hpp>

client& client::instance()
{
    static client instance;
    return instance;
}

void client::init(QQmlContext* context)
{
    if (tempDir.isValid())
        tempPath = tempDir.path();
    else
    {
        qDebug() << "temp directory error :" << tempDir.errorString();
    }

    using namespace Data;
    using namespace People;

    // calculator
    calculator = new Calculator::wrapped_calculator{context, tempPath};

    using namespace Wrapper;

    // accounts
    accounts = new wrapped_list<c_list<c_account>>{context};
    accounts->makeConnections();

    // owners
    owners = new wrapped_nested_list<c_list<c_owner>, c_account>{accounts->get_inner(), context};

    // contacts
    contacts = new wrapped_nested_list<c_list<c_contact>, c_account>{accounts->get_inner(), context};

    using namespace Places;

    // habitat
    habitat = new wrapped_nested_item<c_habitat, c_account>{context};
    habitat->makeConnections(accounts->get_inner());

    // exterior
    exterior = new wrapped_nested_item<c_exterior, c_account>{context};
    exterior->makeConnections(accounts->get_inner());

    // documents
    documents = new wrapped_nested_list<c_list<c_document>, c_account>{accounts->get_inner(), context};

    // users
    users = new wrapped_list<c_list<c_user>>{context};
    users->makeConnections();

    // companies
    companies = new wrapped_list<c_list<c_company>>{context};
    companies->makeConnections();

    // teams
    teams = new wrapped_nested_list<c_list<c_team>, c_company>{companies->get_inner(), context};

    using namespace Interface;

    // bridge
    bridge::instance().init(context);


    QObject::connect(&netManager::instance(),
                     &netManager::loggedIn,
                     [this]
                     (bool success)
                     {
                         if (success)
                         {
                             accounts->get();

                             if (bridge::instance().getClearance()
                                 == user_item::Administrator)
                             {
                                 users->get();
                                 companies->get();
                             }
                         }
                     });

    QObject::connect(&bridge::instance(),
                     &bridge::logout,
                     [this]
                     ()
                     {
                         owners->get_inner()->clear();
                         contacts->get_inner()->clear();
                         habitat->get_inner()->clear();
                         exterior->get_inner()->clear();
                         documents->get_inner()->clear();
                     });

    // Onboarding
    QObject::connect(&bridge::instance(),
                     &bridge::preOnboarding,
                     [this]
                     (int id)
                     {
                         owners->get_inner()->loadFrom(id);
                         habitat->get_inner()->clear();
                         exterior->get_inner()->clear();
                     });

    // Update Owner
    QObject::connect(owners->get_inner(),
                     &c_list<c_owner>::postItemsAppended,
                     [owners = owners->get_inner()] ()
                     {
                         const auto items{owners->items()};
                         qsizetype s{items.size()};

                         if (s < 2) return;

                         const auto previous{items.at(s - 2)};
                         if (previous.civilStatus == owner_item::Maried)
                         {
                             auto item{items.at(s - 1)};

                             item.sex = previous.sex == senior_citizen_item::M
                                            ? senior_citizen_item::F
                                            : senior_citizen_item::M;

                             item.address->street = previous.address->street;
                             item.address->city = previous.address->city;
                             item.address->zip = previous.address->zip;
                             item.address->canton = previous.address->canton;
                             item.civilStatus = previous.civilStatus;
                             item.lastName = previous.lastName;

                             owners->setItemAt(s - 1, item);
                         }
                     });
}

Data::c_list<Data::c_account>* client::get_accounts() const
{
    return accounts->get_inner();
}

Data::c_list<Data::c_document>* client::get_documents() const
{
    return documents->get_inner();
}

Data::c_list<Data::People::c_user>* client::get_users() const
{
    return users->get_inner();
}

QString client::get_tempPath() const
{
    return tempPath;
}

const QTemporaryDir client::tempDir{};

