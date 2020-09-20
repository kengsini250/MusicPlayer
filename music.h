#ifndef MUSIC_H
#define MUSIC_H

#include <QString>

class Music
{
private:
    QString musicPath;
    QString musicName;
public:
    Music() = delete;
    Music(QString path,QString name);
    QString getMusicPath();
    QString getMusicName();

    bool operator ==(const Music& rhs)const{
        return rhs.musicName == musicName;
    }
};

#endif // MUSIC_H
