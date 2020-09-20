#include "music.h"

Music::Music(QString path,QString name)
{
    musicPath = path;
    musicName = name;
}

QString Music::getMusicPath()
{
    return musicPath;
}

QString Music::getMusicName()
{
    return musicName;
}
