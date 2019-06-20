#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>

#include "./code/mymusicplayer.h"
#include "./code/songlist.h"

int main(int argc, char *argv[])
{
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
