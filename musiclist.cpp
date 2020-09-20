#include "musiclist.h"

MusicList::MusicList()
{

}

QList<Music*> MusicList::getMusicList()
{
    return musicList;
}

Music* MusicList::getMusic(QModelIndex currMusic)
{
    QString name = currMusic.data().toString();
    for( int i = 0; i < musicList.count() ; i++)
    {
        if(musicList[i]->getMusicName() == name)
        {
            return musicList[i];
        }
    }
    return nullptr;
}

void MusicList::addMusic(QString path, QString name)
{
    musicList.push_back(new Music(path,name));
    musicCount = musicList.count();
}

void MusicList::addMusic(QString path,QModelIndex currMusic)
{
    QString name = currMusic.data().toString();
    musicList.push_back(new Music(path,name));
    musicCount = musicList.count();
}

void MusicList::deleteMusic(QModelIndex currMusic)
{
    QString name = currMusic.data().toString();
    for( int i = 0; i < musicList.count() ; i++)
    {
        if(musicList[i]->getMusicName() == name)
        {
            musicList.removeAt(i);
        }
    }
}

Music* MusicList::nextMusic()
{
  if(currMusic >= musicCount-1)
        currMusic = 0;
    else
        currMusic++;
    return musicList[currMusic];
}

Music* MusicList::preMusic()
{
    if(currMusic <= 0)
        currMusic = musicCount-1;
    else
        currMusic--;
    return musicList[currMusic];
}

bool MusicList::isNull()
{
  return musicList.isEmpty();
}

void MusicList::updatePlaying(QModelIndex currMusic)
{
    QString name = currMusic.data().toString();
    for( int i = 0; i < musicList.count() ; i++)
    {
        if(musicList[i]->getMusicName() == name)
        {
            this->currMusic = i;
        }
    }
}
