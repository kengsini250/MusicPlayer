#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
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

class MainWindow : public QWidget
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

    bool HideWebViewFlag = false;
protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void openDir(const QDir& p);
    void save();
    void load();
    void settingDialog();
    void showhideWeb();
};
#endif // MAINWINDOW_H
