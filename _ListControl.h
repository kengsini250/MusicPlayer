#ifndef _LISTCONTROL_H
#define _LISTCONTROL_H

#include <QModelIndex>
#include <QString>
#include "music.h"

class ListControl
{
    virtual void addMusic(QString path,QString name) = 0;
    virtual void addMusic(QString path,QModelIndex currMusic) = 0;
    virtual void deleteMusic(QModelIndex currMusic) = 0;
    virtual Music* nextMusic() = 0;//random
    virtual Music* preMusic() = 0;//random
};

#endif // _LISTCONTROL_H
