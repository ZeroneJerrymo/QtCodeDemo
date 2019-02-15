#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // connect(ui->treeWidget, SIGNAL( itemClicked(QTreeWidgetItem* , int )), this, SLOT(slot_expendItem(QTreeWidgetItem* , int )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

