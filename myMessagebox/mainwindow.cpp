#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessagebox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QMessagebox::
}

MainWindow::~MainWindow()
{
    delete ui;
}
