#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QPushButton>

class MenuButton : public QObject
{
  Q_OBJECT

public:
  MenuButton(int h,QWidget *parent);
  ~MenuButton();
  QPushButton* getMenuButton_close();
  QPushButton* getMenuButton_max();
  QPushButton* getMenuButton_min();
private:
  QPushButton* close_;
  QPushButton* max_;
  QPushButton* min_;
Q_SIGNALS:
  void sendExit();
};

#endif
