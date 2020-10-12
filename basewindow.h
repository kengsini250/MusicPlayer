#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtGlobal>

#include <QWidget>
#include <QVBoxLayout>
#include <QPoint>
#include <QMouseEvent>

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
};

#endif
