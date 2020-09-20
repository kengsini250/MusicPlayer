#ifndef MUSICDATA_HPP
#define MUSICDATA_HPP

#include <qglobal.h>

typedef struct
{
    int h,m,s;
}MusicData;

MusicData musicTime(qint64 time);

#endif // MUSICDATA_H
