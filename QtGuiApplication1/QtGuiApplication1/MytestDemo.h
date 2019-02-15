#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MytestDemo.h"

class MytestDemo : public QMainWindow
{
	Q_OBJECT

public:
	MytestDemo(QWidget *parent = Q_NULLPTR);

private:
	Ui::MytestDemoClass ui;
};
