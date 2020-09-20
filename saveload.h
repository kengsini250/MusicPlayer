#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "musiclist.h"
#include <QList>
#include <QFile>
#include <QTextStream>

class SaveLoad:public QObject
{
    Q_OBJECT
public:
    SaveLoad();
    SaveLoad(QString name);
    void setFileName(QString name);
    void setFilePath(QString path);
public slots:
    void save(MusicList& list);
    MusicList load();
private:
    QString filePath;
    QString fileName = "list.txt";
    QFile file;
};

#endif // SAVELOAD_H
