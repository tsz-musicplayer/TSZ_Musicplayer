#ifndef MUSIC_H
#define MUSIC_H
//周敏 音乐
#include <QString>
#include <QVector>
#include <QObject>
//#include "singer.h"
//#include "songlist.h"
#include "string"




class Music: public QObject
{
    Q_OBJECT

    //    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    //    Q_PROPERTY(QString singer READ singer NOTIFY singerChanged)
    //    Q_PROPERTY(QString albumName READ albumName NOTIFY albumNameChanged)

public:
    Music(QString name, QString singer, QString albumName,QString duration,QString size, QString musicSource, QObject *parent = 0);
    //QString formatTime(int ms);


    QString name() const; //得到歌曲名字
    QString singer() const; //得到歌手名字
    QString album() const; //得到歌曲所属专辑名字
    QString source() const; //得到歌曲的音源
    QString duration() const; //得到歌曲的时长
    QString size() const; //得到歌曲的大小



    ~Music();

    //signals:
    //    void nameChanged();
    //    void singerChanged();
    //    void albumNameChanged();




    QString lyric() const;
    void setLyric(const QString &lyric);

private:
    QString m_name; //歌曲名字
    QString m_singer; //歌曲歌手名字
    QString m_album; //歌曲所属专辑名字
    QString m_duration; //时长
    QString m_size; //大小
    QString m_source; //音源
    QString m_lyric; //歌词路径

    //QVector<Singer *> _singer; //歌曲所属歌手
    //Songlist* _album; //歌曲所属专辑
    //QString m_surfaceImage; //歌曲封面
};

#endif // MUSIC_H
