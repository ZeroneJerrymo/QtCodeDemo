#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csetbackgroundwgt.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pWgt   = new CSetBackGroundWgt(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pWgt->show();
}

void MainWindow::on_pushButton_2_clicked()
{
 pWgt-> setBackgroundColor(Qt::blue);
}
