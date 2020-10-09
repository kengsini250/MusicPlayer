#include "basewindow.h"

BaseWindow::BaseWindow(QWidget *parent)
  : QWidget(parent)
{
  setWindowFlag(Qt::FramelessWindowHint);
  setMouseTracking(true);
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
      move(pos() + p);
    });

  //menubar
  connect(menubar,&MenuBar::sendDir,mainwindow,&MainWindow::openDir);
  connect(menubar,&MenuBar::sendSave,mainwindow,&MainWindow::save);
  connect(menubar,&MenuBar::sendLoad,mainwindow,&MainWindow::load);
  connect(menubar, &MenuBar::sendExit, this, &QWidget::close);
  connect(menubar, &MenuBar::sendSetting, mainwindow, &MainWindow::settingDialog);

}

BaseWindow::~BaseWindow()
{
  delete menubar;
  delete mainwindow;
}

void BaseWindow::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
    {
    }
}
