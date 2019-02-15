#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestDemo1.h"

class TestDemo1 : public QMainWindow
{
	Q_OBJECT

public:
	TestDemo1(QWidget *parent = Q_NULLPTR);

private:
	Ui::TestDemo1Class ui;
};
