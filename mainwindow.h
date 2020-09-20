#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QFileInfo>

#include "musiclist.h"
#include "musicdata.h"
#include "saveload.h"
#include "qss/qss.h"
#include "setting/setting.h"

#include "dir.h"
#include <QMediaPlayer>

#include <QPixmap>
#include <QPainter>
#include <QPointer>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateListUI();
    void updateMyList();

    QString backgroundImg = ":/pic/background.jpg";

private:
    Ui::MainWindow *ui;
    QDir path;

    MusicList list;
    QMediaPlayer music;
    SaveLoad saveload;
    Setting* setting;

#ifdef MOVE
    //don't touch !!!
    bool move = false;
    int _w=0, _h=0;
    QPoint oldpos, newpos;
#endif

protected:
    void paintEvent(QPaintEvent *e);

#ifdef MOVE
    void mousePressEvent(QMouseEvent* event)override;
    void mouseMoveEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
#endif
};
#endif // MAINWINDOW_H
