#include <vector>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <access.hpp>
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

#include <Items/senior_citizen_item.hpp>
#include <life_expectency.hpp>

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

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

    QString host{"https://viagetestrive.euclidtradingsystems.com"};

    for(int i = 0; i < argc; i++)
    {
        if (QString::compare(argv[i], "--host") == 0)
        {
            host = argv[i + 1];
            break;
        }
    }

    qDebug() << "Host :" << host;


    Service::access access{host,
                "auth",
                "format=json"};

    using namespace Interface;
    using namespace Service;

    bridge bridge{};
    QObject::connect(&bridge, &bridge::authenticate,
                     &access, &access::authenticate);
    QObject::connect(&access, &access::loggedIn,
                     &bridge, &bridge::onLogin);

    QObject::connect(&bridge, &bridge::requestReport,
                     &access, &access::getReport);

    qmlRegisterUncreatableType<Interface::bridge>("Interface", 1, 0, "Bridge", "");
    context->setContextProperty("bridge", &bridge);

    using namespace Data;
    using namespace Wrapper;

    // accounts
    wrapped_list<item_list<account_item>>
            wrapped_accounts{&access, context};
    wrapped_accounts.makeConnections();

    list_model<account_item> accountModel{};
    accountModel.setList(wrapped_accounts.get_inner());

    account_filter_model accountFilter{&accountModel};
    qmlRegisterUncreatableType<account_filter_model>("Data", 1, 0, "AccountsModel", "");
    context->setContextProperty("accountModel", &accountFilter);

    using namespace People;

    // owners
    wrapped_nested_list<item_list<owner_item>, account_item>
            wrapped_owners{&access, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<owner_item>>("People", 1, 0, "OwnersModel");

    // infants
    wrapped_nested_list<item_list<infant_item>, account_item>
            wrapped_infants{&access, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<infant_item>>("People", 1, 0, "InfantModel");

    using namespace Places;

    // habitat
    wrapped_nested_item<habitat_item, account_item>
            wrapped_habitat{&access, context};
    wrapped_habitat.makeConnections(wrapped_accounts.get_inner());
    // exterior
    wrapped_nested_item<exterior_item, account_item>
            wrapped_exterior{&access, context};
    wrapped_exterior.makeConnections(wrapped_accounts.get_inner());

    // documents
    wrapped_nested_list<item_list<document_item>, account_item>
            wrapped_documents{&access, wrapped_accounts.get_inner(), context};
    qmlRegisterType<list_model<document_item>>("Data", 1, 0, "DocumentModel");
    qmlRegisterType<document_filter_model>("Data", 1, 0, "DocumentFilterModel");

    // users
    wrapped_list<item_list<user_item>>
            wrapped_users{&access, context};
    wrapped_users.makeConnections();

    list_model<user_item> userModel{};
    userModel.setList(wrapped_users.get_inner());

    user_filter_model userFilter{&userModel};
    qmlRegisterUncreatableType<user_filter_model>("People", 1, 0, "UserModel", "");
    context->setContextProperty("userModel", &userFilter);

    QObject::connect(&access, &Service::access::loggedIn,
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

//    simple_item_list<senior_citizen_item> seniors{};
//    seniors.appendItems(2);

//    senior_citizen_item senior_1{};
//    senior_1.birthDay = QDate::fromString("07.10.1957", "dd.MM.yyyy");
//    senior_citizen_item senior_2{};
//    senior_2.sex = senior_citizen_item::sexes::F;
//    senior_2.birthDay = QDate::fromString("26.09.1951", "dd.MM.yyyy");

//    seniors.setItemAt(0, senior_1);
//    seniors.setItemAt(1, senior_2);

//    Calculator::life_expectency exp(&seniors);

//    qDebug() << exp.get_expectency();
    return app.exec();
}
