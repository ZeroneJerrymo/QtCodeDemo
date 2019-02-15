#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "moviepushbutton.h"

#include "dialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    moive = new MoviePushbutton(this);
    ui->tableWidget->setColumnWidth(0,120);
    ui->tableWidget->setCellWidget(0,0,moive) ;
   ui->tableWidget->setRowHeight(0,50);
  //  connect(ui->tableWidget, SIGNAL( itemChanged(QTableWidgetItem *item)), moive, SLOT(slot_startLoad()));

        QMovie*    pmovie = new QMovie("D:\workSpace\Demo\testmap\22222.gif");
        ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
         ui->label->setMovie(pmovie);
         pmovie->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
  //  moive->slot_startLoad();
}
