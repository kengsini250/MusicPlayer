#include "saveload.h"
#include <QDebug>
#include <QMessageBox>

SaveLoad::SaveLoad()
{
    file.setFileName(fileName);
}

SaveLoad::SaveLoad(QString name)
{
    fileName = name;
    file.setFileName(fileName);
}

void SaveLoad::setFileName(QString name)
{
    fileName = name;
}

void SaveLoad::setFilePath(QString path)
{
    filePath = path;
}

void SaveLoad::save(MusicList& list)
{
    QList<Music*> allMusic = list.getMusicList();
    if(allMusic.isEmpty())
    {
        QMessageBox::aboutQt(nullptr,"No Music");
        return;
    }
    //save
    auto p = allMusic.begin();
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    QTextStream out(&file);
    out.setCodec("UTF-8");
    while(p!=allMusic.end())
    {
        out<<(*p)->getMusicPath()<<","<<(*p)->getMusicName()<<",\n";
        p++;
    }
    file.close();
}

MusicList SaveLoad::load()
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in( &file );
    in.setCodec("UTF-8");
    MusicList list;
    while (!in.atEnd()) {
        QString line = in.readLine();
        auto stringlist = line.split(",");
        list.addMusic(stringlist[0],stringlist[1]);
    }
    file.close();
    return list;
}
