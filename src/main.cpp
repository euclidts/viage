#include <vector>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <access.hpp>
#include <smtp.hpp>
#include <bridge.hpp>
#include <Wrapper/wrapped_nested_item.hpp>
#include <Wrapper/wrapped_nested_list.hpp>
#include <Models/list_model.hpp>
#include <Models/urls_model.hpp>
#include <Models/account_filter_model.hpp>
#include <Models/advisor_filter_model.hpp>
#include "Items/advisor_item.hpp"
#include "Items/account_item.hpp"
#include "Items/owner_item.hpp"
#include "Items/habitat_item.hpp"
#include "Items/exterior_item.hpp"
#include "Items/documents_item.hpp"

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

    Interface::bridge bridge{};

    QString host{"https://viagetestrive.euclidtradingsystems.com"};

    for(int i = 0; i < argc; i++)
    {
        if (QString::compare(argv[i], "--host") == 0)
        {
            host = argv[i + 1];
            break;
        }
    }

    qDebug() << "Host : " << host;

    Service::access access{host,
                          "auth",
                          "format=json"};

    QObject::connect(&bridge, &Interface::bridge::authenticate,
            &access, &Service::access::authenticate);
    QObject::connect(&access, &Service::access::loggedIn,
                     &bridge, &Interface::bridge::loggedIn);

    QObject::connect(&bridge, &Interface::bridge::requestReport,
                     [] (const QUrl& url) { qDebug() << url; });

    qmlRegisterUncreatableType<Interface::bridge>("Interface", 1, 0, "Bridge", "");
    context->setContextProperty("bridge", &bridge);

    // accounts
    Data::Wrapper::wrapped_list<Data::item_list<Data::account_item>>
            wrapped_accounts{&access, context};

    Data::list_model<Data::account_item> accountModel{};
    accountModel.setList(wrapped_accounts.getItem());

    Data::account_filter_model accountFilter{&accountModel};
    qmlRegisterUncreatableType<Data::account_filter_model>("Data", 1, 0, "AccountsModel", "");
    context->setContextProperty("accountModel", &accountFilter);

    QObject::connect(&access, &Service::access::loggedIn,
                     [&wrapped_accounts](const bool& success)
    { if (success) wrapped_accounts.get(); });

    // owners
    Data::Wrapper::wrapped_nested_list<Data::item_list<Data::People::owner_item>, Data::account_item>
            wrapped_owners{&access, wrapped_accounts.getItem(), context};
    qmlRegisterType<Data::urls_model>("Data", 1, 0, "UrlsModel");
    qmlRegisterUncreatableType<Data::url_list>("Data", 1, 0, "UrlList", "");
    qmlRegisterType<Data::list_model<Data::People::owner_item>>("People", 1, 0, "OwnersModel");

    // infants
    Data::Wrapper::wrapped_nested_list<Data::item_list<Data::People::infant_item>, Data::account_item>
            wrapped_infants{&access, wrapped_accounts.getItem(), context};
    qmlRegisterType<Data::list_model<Data::People::infant_item>>("People", 1, 0, "InfantModel");

    // habitat
    Data::Wrapper::wrapped_nested_item<Data::Places::habitat_item, Data::account_item>
            wrapped_habitat{&access, wrapped_accounts.getItem(), context};
    // exterior
    Data::Wrapper::wrapped_nested_item<Data::Places::exterior_item, Data::account_item>
            wrapped_exterior{&access, wrapped_accounts.getItem(), context};
    // documents
    Data::Wrapper::wrapped_nested_item<Data::documents_item, Data::account_item>
            wrapped_documents{&access, wrapped_accounts.getItem(), context};

    // advisorrs
    Data::Wrapper::wrapped_list<Data::item_list<Data::People::advisor_item>>
            wrapped_advisors{&access, context};

    Data::list_model<Data::People::advisor_item> advisorModel{};
    advisorModel.setList(wrapped_advisors.getItem());

    Data::advisor_filter_model advisorFilter{&advisorModel};
    qmlRegisterUncreatableType<Data::advisor_filter_model>("People", 1, 0, "AdvisorModel", "");
    context->setContextProperty("advisorModel", &advisorFilter);

    // qml engine
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&bridge, url](QObject* obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
        else
            bridge.set_qmlObject(obj);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
