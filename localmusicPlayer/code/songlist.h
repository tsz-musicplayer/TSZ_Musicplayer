#ifndef SONGLIST_H
#define SONGLIST_H
//周敏 歌单
#include <QList>
#include <QString>
#include <QObject>
#include <QAbstractListModel>

#include "music.h"

class  Songlist : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MusicInfoRoles{ //歌曲信息的角色名
        nameRole = Qt::UserRole + 1,
        singerRole,
        albumRole,
        sourceRole
    };

    Songlist(QString name, QObject *parent = 0);

    Q_INVOKABLE QString next(int index);

    Q_INVOKABLE void clearList();//清空列表
    void addMusic(Music *music); //添加音乐
    int rowCount(const QModelIndex &parent=QModelIndex()) const ; //返回给父项行数
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //返回索引所在项给定角色的存储数据

//   Q_INVOKABLE QList<Music *> getSonglist() const;

    ~Songlist();
protected:
    QHash<int, QByteArray> roleNames() const; //返回模型角色名

private:
    QString m_name; //歌单名字
    QList<Music *> _songlist; //歌单歌曲
};

#endif // SONGLIST_H
