#include <vector>

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
#include <Item/user_item.hpp>
#include <Item/company_item.hpp>
#include <Item/team_item.hpp>
#include <Item/account_item.hpp>
#include <Item/owner_item.hpp>
#include <Item/contact_item.hpp>
#include <Item/habitat_item.hpp>
#include <Item/exterior_item.hpp>
#include <Item/document_item.hpp>
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
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "viage_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();

    using namespace Data;
    using namespace People;

    QString host{"https://viage.euclidtradingsystems.com"};

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
    qmlRegisterType<list_model<senior_citizen_item>>("People", 1, 0, "SeniorCitizenModel");

    // accounts
    wrapped_list<item_list<account_item>>
            wrapped_accounts{&manager, context};
    wrapped_accounts.makeConnections();

    list_model<account_item> accountModel{};
    accountModel.setList(wrapped_accounts.get_inner());

    account_filter_model accountFilter{&accountModel};
    qmlRegisterUncreatableType<account_filter_model>("Data", 1, 0, "AccountModel", "");
    context->setContextProperty("accountModel", &accountFilter);

    // owners
    wrapped_nested_list<item_list<owner_item>, account_item>
            wrapped_owners{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<owner_item>>("People", 1, 0, "OwnersModel");

    // contacts
    wrapped_nested_list<item_list<contact_item>, account_item>
            wrapped_contacts{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<contact_item>>("People", 1, 0, "ContactModel");

    using namespace Places;

    // habitat
    wrapped_nested_item<habitat_item, account_item>
            wrapped_habitat{&manager, context};
    wrapped_habitat.makeConnections(wrapped_accounts.get_inner());
    // exterior
    wrapped_nested_item<exterior_item, account_item>
            wrapped_exterior{&manager, context};
    wrapped_exterior.makeConnections(wrapped_accounts.get_inner());

    // documents
    wrapped_nested_list<item_list<document_item>, account_item>
            wrapped_documents{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<document_item>>("Data", 1, 0, "DocumentModel");
    qmlRegisterType<document_filter_model>("Data", 1, 0, "DocumentFilterModel");

    // users
    wrapped_list<item_list<user_item>>
            wrapped_users{&manager, context};
    wrapped_users.makeConnections();

    list_model<user_item> userModel{};
    userModel.setList(wrapped_users.get_inner());

    user_filter_model userFilter{&userModel};
    user_filter_model selectedUser{&userModel, true};
    qmlRegisterUncreatableType<user_filter_model>("People", 1, 0, "UserModel", "");
    context->setContextProperty("userModel", &userFilter);
    context->setContextProperty("selectedUser", &selectedUser);

    // companies
    wrapped_list<item_list<company_item>>
            wrapped_companies{&manager, context};
    wrapped_companies.makeConnections();
    qmlRegisterType<list_model<company_item>>("Data", 1, 0, "CompaniesModel");

    // teams
    wrapped_nested_list<item_list<team_item>, company_item>
            wrapped_teams{&manager, wrapped_companies.get_inner(), context};
    qmlRegisterType<list_model<team_item>>("Data", 1, 0, "TeamsModel");

    // bridge
    bridge bridge{&manager,
                wrapped_users.get_inner(),
                wrapped_accounts.get_inner(),
                wrapped_documents.get_inner(),
                tempPath};

    qmlRegisterUncreatableType<Interface::bridge>("Interface", 1, 0, "Bridge", "");
    context->setContextProperty("bridge", &bridge);

    QObject::connect(&manager, &Interface::netManager::loggedIn,
                     [
                     &wrapped_accounts,
                     &bridge,
                     &wrapped_users,
                     &wrapped_companies
                     ]
                     (const bool& success)
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

    // Onboarding
    QObject::connect(&bridge,
                     &bridge::requestOwners,
                     wrapped_owners.get_inner(),
                     &item_list<owner_item>::loadFrom);

    // Update Owner
    QObject::connect(wrapped_owners.get_inner(),
                     &item_list<owner_item>::postItemsAppended,
                     [owners = wrapped_owners.get_inner()] ()
    {
        const auto items{owners->items()};
        qsizetype s{items.size()};

        if (s < 2)
            return;

        const auto previous{items.at(s - 2)};
        if (previous.civilStatus == owner_item::Maried)
        {
            auto item{items.at(s - 1)};

            item.sex = previous.sex == senior_citizen_item::M
                    ? senior_citizen_item::F
                    : senior_citizen_item::M;

            item.street = previous.street;
            item.city = previous.city;
            item.zip = previous.zip;
            item.canton = previous.canton;
            item.civilStatus = previous.civilStatus;

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
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&bridge, url](QObject* obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        else
            bridge.setQmlObject(obj);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
