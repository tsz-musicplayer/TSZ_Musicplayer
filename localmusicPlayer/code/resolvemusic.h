#ifndef RESOLVEMUSIC_H
#define RESOLVEMUSIC_H
//苏雪莲
#include "music.h"
#include <QFileInfo>
#include <iostream>

#include "mymusicplayer.h"
using namespace std;

//在C++中引用C语言函数
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

//格式化时间
QString formatTime(int ms)
{
    int ss = 1000000;
    int mi = ss * 60;

    long minute = ms / mi;
    long second = (ms - minute * mi) / ss;

    QString min_tmp = QString("%1").arg(minute, 2, 10, QChar('0'));
    QString sec_tmp = QString("%1").arg(second, 2, 10, QChar('0'));
    QString res = min_tmp + ":" +sec_tmp;
    return res;
}

QString resolveLyric(QString path){
    //            //歌词
    QMap<qint64, QString> lrcMap; //<标签,内容>
    QFile file(path); //打开歌词文件
    file.open(QIODevice::ReadOnly);

    //获取全部歌词
    QString allText = QString(file.readAll());
    //关闭文件
    file.close();
    return allText;

    //            //将歌词按行分解为歌词列表
    //            QStringList lines = allText.split("\n");
    //            //使用正则表达式将时间标签和
    //            QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    //            foreach(QString oneline, lines){
    //                QString tmp = oneline;
    //                // cout << tmp.toStdString() <<endl;
    //                tmp.replace(rx, "");
    //                //一次获取当前行的时间标签，并分别与歌词文本存入QMap
    //                int i =0;
    //                int pos;
    //                cout << "pos:" << pos << endl;
    //                while (i >-5) {
    //                    pos = rx.indexIn(oneline, i);
    //                    cout << "go to while" << "cap: "<< rx.cap(1).toStdString() << endl;
    //                    QString cap = rx.cap(0);

    //                    //将时间标签转换未时间数值，以毫秒为单位
    //                    QRegExp regexp;
    //                    regexp.setPattern("\\d{2}(?=:)");
    //                    regexp.indexIn(cap);
    //                    int minute = regexp.cap(0).toInt();     //分
    //                    regexp.setPattern("\\d{2}(?=\\.)");
    //                    regexp.indexIn(cap);

    //                    int second = regexp.cap(0).toInt();     //秒
    //                    regexp.setPattern("\\d{2}(?=\\])");
    //                    regexp.indexIn(cap);

    //                    int millisecond = regexp.cap(0).toInt();    //毫秒
    //                    qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;

    //                    //插入到lrcMap中
    //                    lrcMap.insert(totalTime, tmp);
    //                    pos += rx.matchedLength();
    //                    pos = rx.indexIn(oneline,pos);

    //                    cout << totalTime << "   " << rx.matchedLength()<< endl;
    //                    i--;
    //                }
    //            }
}

//解析本地音乐
Music *resolveLocalMusic(QFileInfo fileinfo){

    //默认值
    QString name; //歌曲名字
    QString singer = ("未知歌手");      //歌曲歌手名字
    QString album = ("未知专辑");       //歌曲所属专辑名字
    QString duration = ("未知");        //时长
    QString size = ("未知");             //大小
    QString source = fileinfo.absoluteFilePath();           //音源
    QString lyric = ("未知");         //歌词路径

    //解析.mp3文件获取音乐信息
    AVFormatContext *fmt_ctx = NULL;    //在FFmpeg里是一个最大的容器，是输入，输出信息的容器。
    AVDictionaryEntry *tag = NULL;

    av_register_all(); //该函数在所有基于ffmpeg的应用程序中几乎都是第一个被调用的。只有调用了该函数，才能使用复用器，编码器等。

    fmt_ctx = avformat_alloc_context();

    //时长
//    auto d = fmt_ctx->duration;
//    duration = formatTime(d);
//    cout <<"时长： " << duration.toStdString() <<endl;


//    cout <<"source： " << source.toStdString() <<endl;
//    auto d = player->duration();

//    duration = formatTime(d);
//    cout <<"时长： " << duration.toStdString() <<endl;


    //大小
    double tmp = (fileinfo.size()/1024.0)/1024.0;
    size = QString::number(tmp, 'f',1);
    cout << "大小： " << size.toStdString() <<endl;


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
//        cout << "tags:" << endl;
//        cout << tag->key << + ": " << tag->value << endl;
        string tmp = tag->key;
        if(tmp== "album") album = tag->value;
        if(tmp == "artist") singer = tag->value;
        if(tmp == "title") name = tag->value;

    }

    Music *music = new Music(name,singer,album,duration,size,source);

    return music;

}

//Music *resolveOnlineMusic(QString onlineSource){

//    //默认值
//    QString name; //歌曲名字
//    QString singer = ("未知歌手");      //歌曲歌手名字
//    QString album = ("未知专辑");       //歌曲所属专辑名字
//    QString duration = ("未知");        //时长
//    QString size = ("未知");             //大小
//    QString source = onlineSource;           //音源
//    QString lyric = ("未知");         //歌词路径

//    //解析.mp3文件获取音乐信息
//    AVFormatContext *fmt_ctx = NULL;    //在FFmpeg里是一个最大的容器，是输入，输出信息的容器。
//    AVDictionaryEntry *tag = NULL;

//    av_register_all(); //该函数在所有基于ffmpeg的应用程序中几乎都是第一个被调用的。只有调用了该函数，才能使用复用器，编码器等。

//    fmt_ctx = avformat_alloc_context();

//    //时长
////    auto d = fmt_ctx->duration;
////    duration = formatTime(d);
////    cout <<"时长： " << duration.toStdString() <<endl;

//    MyMusicPlayer *player = new MyMusicPlayer();
//    player->setMedia(QUrl(onlineSource));
//    player->play();

//    cout <<"source： " << source.toStdString() <<endl;
//    auto d = player->duration();

//    duration = formatTime(d);
//    cout <<"时长： " << duration.toStdString() <<endl;


//    //大小
//    double tmp = (onlineSource.size()/1024.0)/1024.0;
//    size = QString::number(tmp, 'f',1);
//    cout << "大小： " << size.toStdString() <<endl;


//    char*  ch;
//    QByteArray ba = fileinfo.absoluteFilePath().toLatin1(); // must
//    ch=ba.data();
//    cout << ch << endl;

//    int ret;
//    if(ret = avformat_open_input(&fmt_ctx, ch, NULL, NULL)){
//        cout << "Fail to open file" << endl;
//    }


//    cout << "+++++++" << endl;
//    //读取metadata中所有的tag
//    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))){
////        cout << "tags:" << endl;
////        cout << tag->key << + ": " << tag->value << endl;
//        string tmp = tag->key;
//        if(tmp== "album") album = tag->value;
//        if(tmp == "artist") singer = tag->value;
//        if(tmp == "title") name = tag->value;

//    }

//    Music *music = new Music(name,singer,album,duration,size,source);

//    return music;

//}


#endif // RESOLVEMUSIC_H
