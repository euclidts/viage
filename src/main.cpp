#include <vector>

#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <netManager.hpp>
#include <smtp.hpp>
#include <bridge.hpp>
#include <wrapped_nested_list.hpp>
#include <Models/list_model.hpp>
#include <Models/account_filter_model.hpp>
#include <Models/user_filter_model.hpp>
#include <Models/document_filter_model.hpp>
#include <Items/user_item.hpp>
#include <Items/account_item.hpp>
#include <Items/owner_item.hpp>
#include <Items/habitat_item.hpp>
#include <Items/exterior_item.hpp>
#include <Items/document_item.hpp>
#include <wrapped_calculator.hpp>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

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

    user_item* user{new user_item{}};

    QString host{"https://viagetestrive.euclidtradingsystems.com"};

    for (int i = 0; i < argc; i++)
        if (QString::compare(argv[i], "--host") == 0)
        {
            host = argv[i + 1];
            break;
        }

    qDebug() << "Host :" << host;

    using namespace Interface;

    netManager manager{user,
                host,
                "auth",
                "format=json&jsconfig=TreatEnumAsInteger"};

    using namespace Wrapper;

    // calculator
    Calculator::wrapped_calculator calculator{&manager, context};
    qmlRegisterType<list_model<senior_citizen_item>>("People", 1, 0, "SeniorCitizenModel");

    // accounts
    wrapped_list<item_list<account_item>>
            wrapped_accounts{&manager, context};
    wrapped_accounts.makeConnections();

    list_model<account_item> accountModel{};
    accountModel.setList(wrapped_accounts.get_inner());

    account_filter_model accountFilter{&accountModel};
    qmlRegisterUncreatableType<account_filter_model>("Data", 1, 0, "AccountsModel", "");
    context->setContextProperty("accountModel", &accountFilter);

    // owners
    wrapped_nested_list<item_list<owner_item>, account_item>
            wrapped_owners{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<owner_item>>("People", 1, 0, "OwnersModel");

    // infants
    wrapped_nested_list<item_list<infant_item>, account_item>
            wrapped_infants{&manager, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<infant_item>>("People", 1, 0, "InfantModel");

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

    bridge bridge{&manager, wrapped_documents.get_inner()};

    qmlRegisterUncreatableType<Interface::bridge>("Interface", 1, 0, "Bridge", "");
    context->setContextProperty("bridge", &bridge);

    // send email on documents completed
    QObject::connect(wrapped_documents.get_inner(),
                     &item_list<document_item>::validate,
                     [accounts = wrapped_accounts.get_inner(),
                     documents = wrapped_documents.get_inner(),
                     &manager,
                     &bridge] (int id)
    {
        if (bridge.getDocumentsCompleted())
        {
            const auto state{accounts->item_at_id(id).state};

//            if (state = )
        }
    });

    // users
    wrapped_list<item_list<user_item>>
            wrapped_users{&manager, context};
    wrapped_users.makeConnections();

    list_model<user_item> userModel{};
    userModel.setList(wrapped_users.get_inner());

    user_filter_model userFilter{&userModel};
    qmlRegisterUncreatableType<user_filter_model>("People", 1, 0, "UserModel", "");
    context->setContextProperty("userModel", &userFilter);

    QObject::connect(&manager, &Interface::netManager::loggedIn,
                     [&wrapped_accounts, &wrapped_users](const bool& success)
    {
        if (success)
        {
            wrapped_accounts.get();
            wrapped_users.get();
        }
    });

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
