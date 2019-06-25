#include "music.h"
#include "music.h"
#include "music.h"
#include "music.h"
#include <fstream>
#include <iostream>

#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <QFile>

//在C++中引用C语言函数
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}
using namespace std;

//周敏 音乐
Music::Music(QString name, QString singer, QString albumName, QString duration, QString size, QString musicSource, QObject *parent)
    :QObject(parent),m_name(name), m_singer(singer), m_album(albumName),m_duration(duration),m_size(size), m_source(musicSource)
{

}




//读取歌曲信息
Music *resolveSongInfo(const QString filePath)
{
    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *tag = NULL;

    av_register_all();
//    /root/tmp/天份.mp3
    int ret;
    if(ret = avformat_open_input(&fmt_ctx, "/root/tmp/天份.mp3", NULL, NULL)){
        cout << "Fail to open file" << endl;
    }

    //读取metadata中所有的tag
    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
        cout << "tags:" << endl;
        cout << tag->key << + ": " << tag->value << endl;
    }


//        TagLib::FileRef f(filePath.toLocal8Bit());
//    QString name = QString::fromLocal8Bit(f.tag()->title().toCString(true));
//    QString singer= QString::fromLocal8Bit(f.tag()->artist().toCString(true));
//    QString album= QString::fromLocal8Bit(f.tag()->album().toCString(true));
//    QString time;

//    av_register_all();
//    avformat_network_init();
//    AVFormatContext	*pFormatCtx;

//    pFormatCtx = avformat_alloc_context();

//    if (avformat_open_input(&pFormatCtx, filePath.toLocal8Bit().data(), NULL, NULL) != 0){
//        // qDebug() << "Couldn't open input stream.";
//    } else {
//        if(avformat_find_stream_info(pFormatCtx,NULL)>=0){
//            auto duration = pFormatCtx->duration;
//            time = formatTime(duration);
            //qDebug() << time ;
//        }
//    }

//    QFile file(filePath);
//    file.open(QIODevice::ReadOnly);
//    double size_tmp = (file.size()/1024.0)/1024;
//    QString size = QString::number(size_tmp, 'f', 1);
//    QString path = "file://" + filePath;
//    //    QString path = filePath;

//    Music *music = new Music(name, singer, album, path);
//    return music;
//    //QObject *info = new SongInfo(title, artist, album, time, size,path);
//    //return info;
}

QString Music::name() const
{
    return m_name;
}

QString Music::singer() const
{
    return m_singer;
}

QString Music::album() const
{
    return m_album;
}

Music::~Music()
{

}

QString Music::lyric() const
{
    return m_lyric;
}

void Music::setLyric(const QString &lyric)
{
    m_lyric = lyric;
}


QString Music::duration() const
{
    return m_duration;
}

QString Music::size() const
{
    return m_size;
}

QString Music::source() const
{
    return m_source;
}


