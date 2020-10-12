#include "menubutton.h"

MenuButton::MenuButton(int h,QWidget *parent)
  : QObject(parent)
{
  close_ = new QPushButton(parent);
  close_->setStyleSheet("image:url(:/pic/exit.png);border-radius:5px;");
  close_->setMinimumSize(h,h);
  close_->setMaximumSize(h,h);
  connect(close_,&QPushButton::clicked,[this]{emit sendExit();});

  max_ = new QPushButton(parent);
  max_->setStyleSheet("image:url(:/pic/max.png);border-radius:5px;");
  max_->setMinimumSize(h,h);
  max_->setMaximumSize(h,h);
  connect(max_,&QPushButton::clicked,[this]{emit sendMax();});

  min_ = new QPushButton(parent);
  min_->setStyleSheet("image:url(:/pic/min.png);border-radius:5px;");
  min_->setMinimumSize(h,h);
  min_->setMaximumSize(h,h);
  connect(min_,&QPushButton::clicked,[this]{emit sendMin();});
}

MenuButton::~MenuButton()
{
}

QPushButton* MenuButton::getMenuButton_close()
{
  return close_;
}

QPushButton *MenuButton::getMenuButton_max()
{
  return max_;
}

QPushButton *MenuButton::getMenuButton_min()
{
  return min_;
}
