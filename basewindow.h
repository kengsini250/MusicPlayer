#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPoint>
#include <QMouseEvent>

#ifdef Q_OS_LINUX
#endif

#include "MenuBar/menubar.h"
#include "mainwindow.h"

class BaseWindow : public QWidget
{
	Q_OBJECT

public:
	BaseWindow(QWidget *parent = nullptr);
	~BaseWindow();
private:
	MenuBar* menubar;
	MainWindow* mainwindow;

    bool showMaxFlag = false;
protected:
};

#endif
