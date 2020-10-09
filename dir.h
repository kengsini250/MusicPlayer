#ifndef DIR_H
#define DIR_H

#include <QDir>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QMainWindow>
#include <QFileInfo>

#include "musiclist.h"

void openDir(QWidget* p,QDir* path);
QDir openDir(QWidget* p);
void addFolder(QDir* path,QString _path,MusicList* list);

#endif
