#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenuBar>
#include <QMenu>

#include "../dir.h"

class Menu : public QWidget
{
	Q_OBJECT
public:
	explicit Menu(int h,QWidget* parent = nullptr);
	~Menu();
	QMenuBar* getMenuBar();

private:
	QMenuBar* menubar;
	QMenu* file_;
	QAction* actionOpen;
	QAction* actionSave;
	QAction* actionLoad;
	QAction* actionExit;

	QMenu* setting_;
	QAction* actionSetting;
    QAction* actionShowHide;

Q_SIGNALS:
	void sendExit();
	void sendDir(const QDir& d);
	void sendSave();
	void sendLoad();
	void sendSetting();
    void sendShowHide();
};

#endif
