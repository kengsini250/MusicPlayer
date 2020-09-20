#include "musicdata.h"

MusicData musicTime(qint64 time)
{
    qint64 musicLong = time;//ms
    musicLong /=1000;//ms -> s
    int h = musicLong / 3600;
    int m = (musicLong - h *3600)/60;
    int s = musicLong - h*3600-m*60;
    MusicData t;
    t.h = h;
    t.m = m;
    t.s = s;
    return t;
}
