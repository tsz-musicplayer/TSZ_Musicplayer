#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include <string>
#include "code/client.h"
#include "code/mydb.h"
#include "code/login.h"
#include "code/myJson.h"

//std::string DB_server = "localhost";
//std::string DB_username = "root";
//std::string DB_password = "root";
//std::string DB_name = "mysql";


int main(int argc, char *argv[])
{
   // test login
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //注册组件到QML
    qmlRegisterType<Login>("Login", 1, 0, "Login");

    QQmlApplicationEngine engine;

    QQmlContext* context = engine.rootContext();
    Login* userModel = new Login();
    context->setContextProperty("testUserModel",userModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();

    //test db
    //        MyDB db;
    //        db.initDB(DB_server, DB_username, DB_password, DB_name);
    //        db.createDatabase("Musicplayer");


    //     return app.exec();


    //test client
//            std::string addr, filename;
//            addr = "127.0.0.1";
//            filename = "/root/test.txt";

//            asio::io_service io;

//            std::vector<stru_music> s;
//            try {
//                Client::Pointer c = Client::create(io);
//                //c->downloadFile("/root/tmp/爱的代价.mp3");
//                //c->uploadFile("/root/tmp/爱的代价.mp3");
//                //c->getOnlineSonglist();
//                c->getSonglist("MyMusic");
//                io.run();
//            }
//            catch (std::exception& err) {
//                std::cerr << err.what() << "\n";
//            }
//            MyJson my;
//            my.analysisSonglistJson("MyMusic");
//            stru_music mu;
//            for(auto &sl: s){
//                mu = sl;
//                std::cout << mu.name << std::endl;
//            }

}
