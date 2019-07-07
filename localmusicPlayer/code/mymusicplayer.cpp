#include "mymusicplayer.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QTextCodec>
#include <iostream>

#include "client.h"
#include "resolvemusic.h"
#include "myJson.h"

using namespace std;


//苏雪莲 播放音乐
MyMusicPlayer::MyMusicPlayer()
    :m_playlist("PlayList")
{

}

void MyMusicPlayer::play(QString source)
{
    qDebug()<<"play :..";

    if(online_flag == 0){
    QMediaPlayer::setMedia(QUrl::fromLocalFile(source));
    //QMediaPlayer::setMedia(QUrl("rtsp://127.0.0.1/music/a.mp3"));
    } else if (online_flag == 1){
        //中文转码
        std::cout <<  source.toStdString() << "---" << std::endl;
        std::cout <<  "---" << source.toUtf8().toStdString() << std::endl;
        QMediaPlayer::setMedia(QUrl(source));
    }
    QMediaPlayer::play();
    emit playSuccessful();
}

void MyMusicPlayer::play()
{
    QMediaPlayer::play();
}

void MyMusicPlayer::pause()
{

    qDebug()<<"pause";
    QMediaPlayer ::pause();

}


//void MyMusicPlayer::setPosition(int position)
//{
//    QMediaPlayer::setPosition(position);
//}


void MyMusicPlayer::setDocument(QString path)
{
    m_docPath = path.mid(7, -1);
    std::cout << m_docPath.toStdString() <<std::endl;

    QString fileter;

    m_playlist.clearList();

    QDir mDir(m_docPath);
    QFileInfoList file_info_list = mDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

    foreach (QFileInfo fileinfo, file_info_list) {
        fileter = fileinfo.suffix();
        if(fileter != "mp3")
            continue;
        else{
            qDebug() << fileinfo.absoluteFilePath() << "  " << fileinfo.baseName();

            //Music *music = new Music("name", "singer", "album", "name", "singer", fileinfo.absoluteFilePath());
            //添加文件夹中的音乐到playList
            //music->resolveSongInfo(path);
           //m_playlist.addMusic(music);

           m_playlist.addMusic(resolveLocalMusic(fileinfo));
        }
    }
}

//周敏 解析在线歌单
void MyMusicPlayer::setOnlineSonglist(QString filePath)
{
    asio::io_service io;

    std::vector<stru_music> s;
    try {
        Client::Pointer c = Client::create(io);
        c->getSonglist(filePath.toStdString());
        io.run();
    }
    catch (std::exception& err) {
        std::cerr << err.what() << "\n";
    }

    m_playlist.clearList();
    std::cout << filePath.toStdString() << std::endl;
    filePath = "./" + filePath + ".json";
    MyJson json;
    std::vector<stru_music> music = json.analysisSonglistJson(filePath.toStdString());

    std::cout << music.size() << std::endl;
    for(auto &s : music){
        Music *m;
        m = new Music(QString::fromStdString(s.name),
                QString::fromStdString(s.singer),
                QString::fromStdString(s.album),
                QString::fromStdString(s.duration),
                QString::fromStdString(s.size),
                QString::fromStdString(s.source));
        //std::cout << m->name().toStdString() << std::endl;
        m_playlist.addMusic(m);
    }
}

Songlist& MyMusicPlayer::playlist()
{
    return m_playlist;
}

void MyMusicPlayer::play(QString source, QString onlineflage)
{
    qDebug()<<"play :..";

    //中文转码
    std::cout <<  source.toStdString() << "---" << std::endl;
    std::cout <<  "---" << source.toUtf8().toStdString() << std::endl;

    QMediaPlayer::setMedia(QUrl(source));
    QMediaPlayer::play();
    emit playSuccessful();
}

//void PlayMusic::setUrl(/*QString url*/)
//{
//    //m_url = url;
//    QMediaPlayer::setMedia(QUrl::fromLocalFile(QStringLiteral("/root/tmp/爱的代价.mp3")));
//    QMediaPlayer::setMedia(QUrl::fromLocalFile(QStringLiteral(url)));
//}
