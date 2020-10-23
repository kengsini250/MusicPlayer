#include "basewindow.h"

BaseWindow::BaseWindow(QWidget *parent)
    : QWidget(parent)
{
#ifdef Q_OS_WIN
    setWindowFlag(Qt::FramelessWindowHint);
#endif
//    setMouseTracking(true);
    setMinimumHeight(800);
    setMinimumWidth(1200);

    menubar = new MenuBar(1200,parent);
    mainwindow = new MainWindow(parent);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setMenuBar(menubar);
    layout->addWidget(mainwindow);
    setLayout(layout);

    menubar->show();
    mainwindow->show();

    //position
    connect(menubar, &MenuBar::newPos, [this](const QPoint& p) {
        qDebug()<<pos();
        move(pos()+p);
        qDebug()<<pos();
    });

    //menubar
    connect(menubar,&MenuBar::sendDir,mainwindow,&MainWindow::openDir);
    connect(menubar,&MenuBar::sendSave,mainwindow,&MainWindow::save);
    connect(menubar,&MenuBar::sendLoad,mainwindow,&MainWindow::load);
    connect(menubar,&MenuBar::sendSetting, mainwindow, &MainWindow::settingDialog);
    connect(menubar,&MenuBar::sendShowHide,mainwindow,&MainWindow::showhideWeb);
    connect(menubar,&MenuBar::sendExit, this, &QWidget::close);

#ifdef Q_OS_WINDOWS
    connect(menubar,&MenuBar::sendMin, this, &QWidget::showMinimized);
    connect(menubar,&MenuBar::sendMax,[this]{
        if(false == showMaxFlag){
            showMaxFlag = true;
            showMaximized();
        }else{
            showMaxFlag = false;
            showNormal();
        }
    });
#endif
}

BaseWindow::~BaseWindow()
{
    delete menubar;
    delete mainwindow;
}
