#include "mymusicplayer.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <iostream>
#include <QDebug>
#include <QTextCodec>

#include <iostream>
//在C++中引用C语言函数
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
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
    QMediaPlayer::play();
    emit playSuccessful();
}

void MyMusicPlayer::pause()
{

    qDebug()<<"pause";
    QMediaPlayer ::pause();

}


void MyMusicPlayer::setPosition(int position)
{
    QMediaPlayer::setPosition(position);
}

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


            QString name;
            QString singer("未知歌手"); //歌手
            QString album("未知专辑"); //专辑

            //获取音乐信息
            //name = fileinfo.baseName();

            AVFormatContext *fmt_ctx = NULL;
            AVDictionaryEntry *tag = NULL;

            av_register_all();
        //    /root/tmp/天份.mp3
            char*  ch;
            QByteArray ba = fileinfo.absoluteFilePath().toLatin1(); // must
            ch=ba.data();
            cout << ch << endl;

            int ret;
            if(ret = avformat_open_input(&fmt_ctx, ch, NULL, NULL)){
                cout << "Fail to open file" << endl;
            }
cout << "+++++++" << endl;
            //读取metadata中所有的tag
            while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
                cout << "tags:" << endl;
                cout << tag->key << + ": " << tag->value << endl;
                string tmp = tag->key;
                if(tmp== "album") album = tag->value;
                if(tmp == "artist") singer = tag->value;
                if(tmp == "title") name = tag->value;
            }

            //Music *music = new Music(name, singer, album, fileinfo.absoluteFilePath());
            //添加文件夹中的音乐到playList
            //music->resolveSongInfo(path);
           // m_playlist.addMusic(music->resolveSongInfo(path));
            m_playlist.addMusic(new Music(name, singer, album, fileinfo.absoluteFilePath()));
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
