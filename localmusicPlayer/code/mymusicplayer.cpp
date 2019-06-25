#include "mymusicplayer.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QTextCodec>

#include <iostream>

#include "resolvemusic.h"

using namespace std;


//苏雪莲 播放音乐
MyMusicPlayer::MyMusicPlayer()
    :m_playlist("PlayList")
{

}

void MyMusicPlayer::play(QString source)
{
    qDebug()<<"play :..";

    QMediaPlayer::setMedia(QUrl::fromLocalFile(source));
    //QMediaPlayer::setMedia(QUrl("rtsp://192.168.42.59/a.mp3"));
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



            //Music *music = new Music(name, singer, album, fileinfo.absoluteFilePath());
            //添加文件夹中的音乐到playList
            //music->resolveSongInfo(path);
            //m_playlist.addMusic(music->resolveSongInfo(path));

            m_playlist.addMusic(resolveLocalMusic(fileinfo));





        }
    }

}

Songlist& MyMusicPlayer::playlist()
{
    return m_playlist;
}

void MyMusicPlayer::playOnline(QString source)
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
