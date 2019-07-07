#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>

#include "./code/mymusicplayer.h"
#include "./code/songlist.h"
#include "./code/client.h"
#include "./code/myJson.h"

void initdata()
{
    asio::io_service io;

    std::vector<stru_music> s;
    try {
        Client::Pointer c = Client::create(io);
        c->getSonglist("华语");
        io.run();
    }
    catch (std::exception& err) {
        std::cerr << err.what() << "\n";
    }
   // MyJson my;
    //my.analysisSonglistJson("MyMusic");
//    stru_music mu;
//    for(auto &sl: s){
//        mu = sl;
//        std::cout << mu.name << std::endl;
//    }

}

int main(int argc, char *argv[])
{
    //initdata();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // qmlRegisterType<MyMusicPlayer>("MyMusicPlayer", 1, 0, "MyMusicPlayer");

    QQmlApplicationEngine engine;

    MyMusicPlayer play;
    Songlist &playlist = play.playlist();
    //    playlist.addMusic(new Music("music1", "singer1", "album1", " "));
    //    playlist.addMusic(new Music("music2", "singer2", "album2", " "));
    //    playlist.addMusic(new Music("music3", "singer3", "album3", " "));

    engine.rootContext()->setContextProperty("myPlayListModel", QVariant::fromValue(&playlist));
    engine.rootContext()->setContextProperty("myPlayer", QVariant::fromValue(&play));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
