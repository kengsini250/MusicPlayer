#include "menu.h"

Menu::Menu(int h,QWidget *parent)
  :QWidget(parent)
{
  menubar = new QMenuBar(parent);
  menubar->setMinimumHeight(h);
  menubar->setMaximumHeight(h);
  file_ = new QMenu("File");
  setting_ = new QMenu("Setting");
  menubar->addMenu(file_);
  menubar->addMenu(setting_);

  //open
  actionOpen = new QAction("Open");
  file_->addAction(actionOpen);
  connect(actionOpen,&QAction::triggered,[this]{
      emit sendDir(openDir(this));
    });

  //save
  actionSave=new QAction("Save");
  file_->addAction(actionSave);
  connect(actionSave,&QAction::triggered,[this]{
      emit sendSave();
    });

  //load
  actionLoad=new QAction("Load");
  file_->addAction(actionLoad);
  connect(actionLoad,&QAction::triggered,[this]{
      emit sendLoad();
    });

  //exit
  actionExit = new QAction("Exit");
  file_->addAction(actionExit);
  connect(actionExit,&QAction::triggered,[this]{emit sendExit();});

  //setting
  actionSetting = new QAction("Property");
  setting_->addAction(actionSetting);
  connect(actionSetting,&QAction::triggered,[this]{emit sendSetting();});
}

Menu::~Menu()
{
  delete actionOpen;
  delete actionSave;
  delete actionLoad;
  delete actionExit;
  delete actionSetting;

  delete menubar;
  delete setting_;
}

QMenuBar* Menu::getMenuBar()
{
  return menubar;
}
