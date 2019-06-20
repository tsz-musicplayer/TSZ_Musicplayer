#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "login.h"

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

//    const QUrl url(QStringLiteral("qrc:/login.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

    return app.exec();
}
