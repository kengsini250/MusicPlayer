#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QList>

#include "music.h"
#include "_ListControl.h"

class MusicList :public ListControl
{

private:
    QList<Music*> musicList;
    int currMusic = -1;
    int musicCount = -1;
public:
    MusicList();
    QList<Music*> getMusicList();
    Music* getMusic(QModelIndex currMusic);
    void addMusic(QString path,QString name) override;
    void addMusic(QString path, QModelIndex currMusic) override;
    void deleteMusic(QModelIndex currMusic) override;
    Music* nextMusic() override;
    Music* preMusic() override;
    bool isNull();

    void updatePlaying(QModelIndex currMusic);
};

#endif // MUSICLIST_H
