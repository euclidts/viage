#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QTranslator>

#include <client.hpp>
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

//    QString tempPath{};
//    QTemporaryDir tempDir{};
//    if (tempDir.isValid())
//        tempPath = tempDir.path();
//    else
//    {
//        qDebug() << "temp directory error :" << tempDir.errorString();
//        return 4;
//    }

    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();

    QTranslator translator;
    if (translator.load(QLocale(), "viage", "_", ":/qm_files/"))
        app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    auto context = engine.rootContext();

    using namespace Data;
    using namespace People;

//    QString host{"https://viage.euclidtradingsystems.com"};
    QString host{"https://viagetestrive.euclidtradingsystems.com"};
//    QString host{"http://127.0.0.0:8080"};

    for (int i = 0; i < argc; i++)
        if (QString::compare(argv[i], "--host") == 0)
        {
            host = argv[i + 1];
            break;
        }

    qDebug() << "Host :" << host;

    using namespace Interface;

    netManager::instance().init(host,
                                "auth",
                                "format=json&jsconfig=TreatEnumAsInteger");

    client::instance().init(context);

    // qml engine
    const QUrl url(QStringLiteral("qrc:/ui/main.qml"));
    QObject::connect(&engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url]
        (QObject* obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
            else
                bridge::instance().setQmlObject(obj);
        }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
