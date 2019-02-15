#ifndef SKINWINDOW_H
#define SKINWINDOW_H

#include "BasicWindow.h"
#include "ui_skinwindow.h"

class SkinWindow : public BasicWindow
{
	Q_OBJECT

public:
	SkinWindow(QWidget *parent = 0);
	~SkinWindow();

public:
	void initControl();

private:
	Ui::SkinWindow ui;
};

#endif // SKINWINDOW_H
