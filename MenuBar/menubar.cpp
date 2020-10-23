#include "menubar.h"

MenuBar::MenuBar(int _w,QWidget *parent):QWidget(parent),w(_w)
{
  setAutoFillBackground(true);
  setMinimumWidth(w);
  int h=25;

  setWindowFlag(Qt::FramelessWindowHint);
  setMinimumHeight(h);
  setMaximumHeight(h);

  QHBoxLayout* layout = new QHBoxLayout;
  layout->setMargin(0);

  //menu
  menu = new Menu(h,this);
  connect(menu,&Menu::sendDir,[this](const QDir& d){emit sendDir(d);});
  connect(menu,&Menu::sendSave,[this]{emit sendSave();});
  connect(menu,&Menu::sendLoad,[this]{emit sendLoad();});
  connect(menu,&Menu::sendExit,[this] {emit sendExit();});
  connect(menu,&Menu::sendSetting,[this] {emit sendSetting();});
  connect(menu,&Menu::sendShowHide,[this]{emit sendShowHide();});
  layout->addWidget(menu);

//  QSpacerItem* s = new QSpacerItem(1000,h);
//  layout->addSpacerItem(s);

  //button
#ifdef Q_OS_WINDOWS
  button = new MenuButton(h,this);
  layout->addWidget(button->getMenuButton_min());
  layout->addWidget(button->getMenuButton_max());
  layout->addWidget(button->getMenuButton_close());
  connect(button, &MenuButton::sendExit, [this] {emit sendExit(); });
  connect(button, &MenuButton::sendMin, [this] {emit sendMin(); });
  connect(button, &MenuButton::sendMax, [this] {emit sendMax(); });
#endif

  setLayout(layout);

  timer = new QTimer;
  timer->start(100);
  connect(timer,&QTimer::timeout,[this]{update();});
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
      moveFlag = true;
      oldpos = event->globalPos();
      qDebug()<<"old pos : "<<oldpos;
    }
  QWidget::mousePressEvent(event);
}

void MenuBar::mouseMoveEvent(QMouseEvent* event)
{
  if ((event->buttons() & Qt::LeftButton) && moveFlag)
    {
      newpos = event->globalPos();
      qDebug()<<"new pos : "<<newpos;
      emit newPos(newpos - oldpos);
      oldpos = newpos;
    }
  QWidget::mouseMoveEvent(event);
}

void MenuBar::mouseReleaseEvent(QMouseEvent* event)
{
  if ((event->buttons() == Qt::LeftButton) && moveFlag)
    {
      moveFlag = false;
    }
  QWidget::mouseReleaseEvent(event);
}

void MenuBar::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)
  if(Animation){
      QPainter p(this);
      p.setPen(Qt::NoPen);
      QLinearGradient linear(QPointF(0, 10), QPointF(w, 10));

//      linear.setColorAt(0,QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255)));
//      linear.setColorAt(1,QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255)));
      linear.setColorAt(0,QColor(R1, G1--, B1--));
      linear.setColorAt(1,QColor(R1, G2++, B2++));
      if(G1 == Gmin){
          G1=Gmax;G2=Gmin;B1=Bmax;B2=Bmin;
        }

      p.setBrush(linear);
      p.drawRect(rect());
    }
}

