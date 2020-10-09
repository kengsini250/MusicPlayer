#include "menubar.h"

MenuBar::MenuBar(int _w,QWidget *parent):QWidget(parent),w(_w)
{
  setMinimumWidth(w);
  //setMinimumWidth(500);
  int h=20;

  setWindowFlag(Qt::FramelessWindowHint);
  setMinimumHeight(h);
  setMaximumHeight(h);
  //setStyleSheet("background-color:green;");

  QHBoxLayout* layout = new QHBoxLayout;
  layout->setMargin(0);

  //menu
  menu = new Menu(h,this);
  connect(menu,&Menu::sendDir,[this](const QDir& d){emit sendDir(d);});
  connect(menu,&Menu::sendSave,[this]{emit sendSave();});
  connect(menu,&Menu::sendLoad,[this]{emit sendLoad();});
  connect(menu, &Menu::sendExit, [this] {emit sendExit(); });
  connect(menu, &Menu::sendSetting, [this] {emit sendSetting(); });
  layout->addWidget(menu);

//  QSpacerItem* s = new QSpacerItem(1000,h);
//  layout->addSpacerItem(s);

  //button
  button = new MenuButton(h,this);
  layout->addWidget(button->getMenuButton_min());
  layout->addWidget(button->getMenuButton_max());
  layout->addWidget(button->getMenuButton_close());
  connect(button, &MenuButton::sendExit, [this] {emit sendExit(); });

  setLayout(layout);
}

MenuBar::~MenuBar()
{
  delete menu;
  delete button;
}

void MenuBar::mousePressEvent(QMouseEvent* event)
{
  if (event->button() == Qt::LeftButton)
    {
      move = 1;
      oldpos = event->globalPos();
    }
}

void MenuBar::mouseMoveEvent(QMouseEvent* event)
{
  if ((event->buttons() & Qt::LeftButton) && move)
    {
      newpos = event->globalPos();
      auto p = newpos - oldpos;
      oldpos = newpos;
      emit newPos(p);
    }
}

void MenuBar::mouseReleaseEvent(QMouseEvent* event)
{
  if ((event->buttons() & Qt::LeftButton) && move)
    {
      move = false;
    }
}

