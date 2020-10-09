#ifndef MENUBAR_H
#define MENUBAR_H

#include <QDebug>

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

#include <QHBoxLayout>
#include <QSpacerItem>
#include "menu.h"
#include "menubutton.h"

class MenuBar : public QWidget
{
	Q_OBJECT

public:
	explicit MenuBar(int w = 1200,QWidget *parent = nullptr);
	~MenuBar();

private:
	bool move = false;
	QPoint oldpos, newpos;

	Menu* menu;
	MenuButton* button;
	int w = 1200;
protected:
	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event)override;

Q_SIGNALS:
	void newPos(const QPoint&);
	void sendExit();
	void sendDir(const QDir& d);
	void sendSave();
	void sendLoad();
	void sendSetting();
};
#endif // MENUBAR_H
