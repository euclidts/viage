#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <netManager.hpp>
#include <bridge.hpp>
#include <wrapped_nested_list.hpp>
#include <list_model.hpp>
#include <account_filter_model.hpp>
#include <user_filter_model.hpp>
#include <document_filter_model.hpp>
#include <Item/c_user.hpp>
#include <Item/c_company.hpp>
#include <Item/c_team.hpp>
#include <Item/c_account.hpp>
#include <Item/c_owner.hpp>
#include <Item/c_contact.hpp>
#include <Item/c_habitat.hpp>
#include <Item/c_exterior.hpp>
#include <Item/c_document.hpp>
#include <wrapped_calculator.hpp>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QString tempPath{};
    QTemporaryDir tempDir{};
    if (tempDir.isValid())
        tempPath = tempDir.path();
    else
    {
        qDebug() << "temp directory error :" << tempDir.errorString();
        return 4;
    }

    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();

    QTranslator translator;
    if (translator.load(QLocale(), "viage", "_", ":/qm_files/"))
        app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();

    using namespace Data;
    using namespace People;

    QString host{"https://viage.euclidtradingsystems.com"};
//    QString host{"https://viagetestrive.euclidtradingsystems.com"};
//    QString host{"http://127.0.0.0:8080"};

    for (int i = 0; i < argc; i++)
        if (QString::compare(argv[i], "--host") == 0)
        {
            host = argv[i + 1];
            break;
        }

    qDebug() << "Host :" << host;

    using namespace Interface;

    netManager manager{host,
                       "auth",
                       "format=json&jsconfig=TreatEnumAsInteger"};

    using namespace Wrapper;

    // calculator
    Calculator::wrapped_calculator calculator{&manager, context, tempPath};
    qmlRegisterType<list_model<c_senior_citizen>>("People", 1, 0, "SeniorCitizenModel");

    // accounts
    wrapped_list<c_list<c_account>>
        wrapped_accounts{&manager, context};
    wrapped_accounts.makeConnections();

    list_model<c_account> accountModel{};
    accountModel.setList(wrapped_accounts.get_inner());

    account_filter_model accountFilter{&accountModel};
    qmlRegisterUncreatableType<account_filter_model>("Data", 1, 0, "AccountModel", "");
    context->setContextProperty("accountModel", &accountFilter);

    // owners
    wrapped_nested_list<c_list<c_owner>, c_account>
        wrapped_owners{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<c_owner>>("People", 1, 0, "OwnersModel");

    // contacts
    wrapped_nested_list<c_list<c_contact>, c_account>
        wrapped_contacts{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<c_contact>>("People", 1, 0, "ContactModel");

    using namespace Places;

    // habitat
    wrapped_nested_item<c_habitat, c_account>
        wrapped_habitat{&manager, context};
    wrapped_habitat.makeConnections(wrapped_accounts.get_inner());
    // exterior
    wrapped_nested_item<c_exterior, c_account>
        wrapped_exterior{&manager, context};
    wrapped_exterior.makeConnections(wrapped_accounts.get_inner());

    // documents
    wrapped_nested_list<c_list<c_document>, c_account>
        wrapped_documents{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<c_document>>("Data", 1, 0, "DocumentModel");
    qmlRegisterType<document_filter_model>("Data", 1, 0, "DocumentFilterModel");

    // users
    wrapped_list<c_list<c_user>>
        wrapped_users{&manager, context};
    wrapped_users.makeConnections();

    list_model<c_user> userModel{};
    userModel.setList(wrapped_users.get_inner());

    user_filter_model userFilter{&userModel};
    user_filter_model selectedUser{&userModel, true};
    qmlRegisterUncreatableType<user_filter_model>("People", 1, 0, "UserModel", "");
    context->setContextProperty("userModel", &userFilter);
    context->setContextProperty("selectedUser", &selectedUser);

    // companies
    wrapped_list<c_list<c_company>>
        wrapped_companies{&manager, context};
    wrapped_companies.makeConnections();
    qmlRegisterType<list_model<c_company>>("Data", 1, 0, "CompaniesModel");

    // teams
    wrapped_nested_list<c_list<c_team>, c_company>
        wrapped_teams{&manager, wrapped_companies.get_inner(), context};
    qmlRegisterType<list_model<c_team>>("Data", 1, 0, "TeamsModel");

    // bridge
    bridge bridge{&manager,
                  wrapped_users.get_inner(),
                  wrapped_accounts.get_inner(),
                  wrapped_documents.get_inner(),
                  tempPath};

    qmlRegisterUncreatableType<Interface::bridge>("Interface", 1, 0, "Bridge", "");
    context->setContextProperty("bridge", &bridge);

    QObject::connect(&manager, &Interface::netManager::loggedIn,
                     [&wrapped_accounts,
                      &bridge,
                      &wrapped_users,
                      &wrapped_companies]
                     (bool success)
                     {
                         if (success)
                         {
                             wrapped_accounts.get();

                             if (bridge.getClearance() == user_item::Administrator)
                             {
                                 wrapped_users.get();
                                 wrapped_companies.get();
                             }
                         }
                     });

    QObject::connect(&bridge,
                     &bridge::logout,
                     [owners = wrapped_owners.get_inner(),
                      contacts = wrapped_contacts.get_inner(),
                      habitat = wrapped_habitat.get_inner(),
                      exterior = wrapped_exterior.get_inner(),
                      documents = wrapped_documents.get_inner()]
                     ()
                     {
                         owners->clear();
                         contacts->clear();
                         habitat->clear();
                         exterior->clear();
                         documents->clear();
                     });

    // Onboarding
    QObject::connect(&bridge,
                     &bridge::preOnboarding,
                     [owners = wrapped_owners.get_inner(),
                      habitat = wrapped_habitat.get_inner(),
                      exterior = wrapped_exterior.get_inner()]
                     (int id)
                     {
                         owners->loadFrom(id);
                         habitat->clear();
                         exterior->clear();
                     });

    // Update Owner
    QObject::connect(wrapped_owners.get_inner(),
                     &c_list<c_owner>::postItemsAppended,
                     [owners = wrapped_owners.get_inner()] ()
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

    // Hiering
    QObject::connect(&bridge,
                     &bridge::requestUser,
                     &selectedUser,
                     &user_filter_model::forceFilterRole);

    // qml engine
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [&bridge, url](QObject* obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
            else
                bridge.setQmlObject(obj);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
