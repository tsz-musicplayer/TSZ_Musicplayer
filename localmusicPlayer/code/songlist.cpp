#include "songlist.h"
//周敏 歌单
Songlist::Songlist(QString name, QObject *parent)
    :QAbstractListModel(parent), m_name(name)
{

}

QString Songlist::next(int index)
{
   return this->_songlist[index+1]->source();

}

void Songlist::clearList()
{
    beginResetModel();
    _songlist.clear();
    endResetModel();
}

void Songlist::addMusic(Music *music)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _songlist.append(music);
    endInsertRows();
}

int Songlist::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _songlist.count();
}

QVariant Songlist::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row()>_songlist.count())
        return QVariant();
    const Music *music = _songlist[index.row()]; //得到音乐
    if(role == MusicInfoRoles::nameRole)
        return music->name();
    else if(role == MusicInfoRoles::singerRole)
        return music->singer();
    else if(role == MusicInfoRoles::albumRole)
        return music->albumName();
    else if(role == MusicInfoRoles::sourceRole)
        return music->source();
    return QVariant();
}

//QList<Music *> Songlist::getSonglist() const
//{
//    return _songlist;
//}

Songlist::~Songlist()
{

}

QHash<int, QByteArray> Songlist::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(MusicInfoRoles::nameRole, "name");
    roles.insert(MusicInfoRoles::singerRole, "singer");
    roles.insert(MusicInfoRoles::albumRole, "album");
    roles.insert(MusicInfoRoles::sourceRole, "source");

    return roles;
}
