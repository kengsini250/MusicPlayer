#ifndef MENUBAR_H
#define MENUBAR_H

#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QRandomGenerator>

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

#include <QHBoxLayout>
#include <QSpacerItem>
#include "menu.h"
#include "menubutton.h"

class MenuBar final: public QWidget
{
  Q_OBJECT

public:
  explicit MenuBar(int w = 1200,QWidget *parent = nullptr);
  ~MenuBar();

private:
  //----------------------
  bool moveFlag = false;
  QPoint oldpos, newpos;
  bool Animation = true;
  QTimer* timer;
  //----------------------

  Menu* menu;
  MenuButton* button;
  int w;
protected:
  void mousePressEvent(QMouseEvent* event)override;
  void mouseMoveEvent(QMouseEvent* event)override;
  void mouseReleaseEvent(QMouseEvent* event)override;
  void paintEvent(QPaintEvent *event)override;
Q_SIGNALS:
  void newPos(const QPoint&);
  void sendExit();
  void sendDir(const QDir& d);
  void sendSave();
  void sendLoad();
  void sendSetting();
  void sendShowHide();

  void sendMin();
  void sendMax();
};
#endif // MENUBAR_H
