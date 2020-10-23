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

#ifdef Q_OS_WINDOWS
  QPushButton* getMenuButton_close();
  QPushButton* getMenuButton_max();
  QPushButton* getMenuButton_min();
#endif

private:

#ifdef Q_OS_WINDOWS
  QPushButton* close_;
  QPushButton* max_;
  QPushButton* min_;
#endif

Q_SIGNALS:

#ifdef Q_OS_WINDOWS
  void sendExit();
  void sendMin();
  void sendMax();
#endif
};

#endif
