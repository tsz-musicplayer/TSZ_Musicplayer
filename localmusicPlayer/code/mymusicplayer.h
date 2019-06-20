#ifndef MYMUSICPLAYER_H
#define MYMUSICPLAYER_H
#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include "songlist.h"


//苏雪莲 播放音乐
class MyMusicPlayer : public QMediaPlayer
{
    Q_OBJECT
public:
    MyMusicPlayer();

//    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)


    Q_INVOKABLE void play(QString source);
    Q_INVOKABLE void pause();
    Q_INVOKABLE void setPosition(int position);

    Q_INVOKABLE void setDocument(QString path);
    Q_INVOKABLE Songlist& playlist();
    Q_INVOKABLE void playOnline(QString source);

//    Q_INVOKABLE void setUrl(/*QString url*/);

signals:
    void playSuccessful();
//    void urlChanged();



private:
    // QString m_url;
    QString m_docPath;
    QList<Music *> _allMusic;
    Songlist m_playlist;
};

#endif // MYMUSICPLAYER_H
