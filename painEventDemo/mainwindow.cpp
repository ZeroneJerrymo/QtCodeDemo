#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paineventtest.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // rgb(0, 255, 255);
}

MainWindow::~MainWindow()
{
    delete ui;
}
