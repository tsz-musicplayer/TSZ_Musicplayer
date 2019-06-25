#include "songlist.h"
//周敏 歌单
Songlist::Songlist(QString name, QObject *parent)
    :QAbstractListModel(parent), m_name(name)
{

}

QString Songlist::next(int index)
{
   return this->_musics[index+1]->source();

}

void Songlist::clearList()
{
    beginResetModel();
    _musics.clear();
    endResetModel();
}

void Songlist::addMusic(Music *music)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _musics.append(music);
    endInsertRows();
}

int Songlist::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _musics.count();
}

QVariant Songlist::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row()>_musics.count())
        return QVariant();
    const Music *music = _musics[index.row()]; //得到音乐
    if(role == MusicInfoRoles::nameRole)
        return music->name();
    else if(role == MusicInfoRoles::singerRole)
        return music->singer();
    else if(role == MusicInfoRoles::albumRole)
        return music->album();
    else if(role == MusicInfoRoles::sourceRole)
        return music->source();
    else if(role == MusicInfoRoles::duration)
        return music->duration();
    else if(role == MusicInfoRoles::size)
        return music->size() + "M";
    return QVariant();
}

QString Songlist::getMusicSource(int index)
{
    return _musics.at(index)->source();
}

QString Songlist::getMusicName(int index)
{
    return _musics.at(index)->name();
}

int Songlist::musicCount()
{
    return _musics.count();
}

QString Songlist::getMusicLyric(int index)
{
    return _musics.at(index)->lyric();
}

bool Songlist::isEnd(int id)
{
    return id != _musics.count()-1;
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
    roles.insert(MusicInfoRoles::duration, "duration");
    roles.insert(MusicInfoRoles::size, "size");

    return roles;
}
