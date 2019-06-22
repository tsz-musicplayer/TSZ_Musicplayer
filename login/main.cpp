#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "login.h"
#include "mydb.h"


using std::string;

string DB_server = "localhost";
string DB_username = "root";
string DB_password = "root";
string DB_name = "mysql";

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //注册组件到QML
    qmlRegisterType<Login>("Login", 1, 0, "Login");

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    Login* userModel = new Login();
    context->setContextProperty("testUserModel",userModel);

    engine.load(QUrl(QStringLiteral("qrc:/login.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    MyDB db;
    db.initDB(DB_server, DB_username, DB_password, DB_name);
//    db.createDatabase("Musicplayer");
    db.useDatabase("Musicplayer");
//    db.createPassworddbTable();
//    db.createsongListLabTable("tt");
//    db.createsongListTable("tt", "Like");
//    db.createMusicTable();

//    db.querysongListLab("tt");
//    db.querysongList("Like");
//    db.queryMusic("M1");

//    db.search("n2");
//    db.addsongList("tt","LOVE");
    db.addMusic("Like","P5");
//    db.deletesongListTable("tt","Like");
    db.delectMusic("Like", "P1");

    //    db.queryUserInfo("tt","123");
    //    const QUrl url(QStringLiteral("qrc:/login.qml"));
    //    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    //                     &app, [url](QObject *obj, const QUrl &objUrl) {
    //        if (!obj && url == objUrl)
    //            QCoreApplication::exit(-1);
    //    }, Qt::QueuedConnection);
    //    engine.load(url);

    return app.exec();
}
