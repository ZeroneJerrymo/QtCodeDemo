#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Form * testLib = new Form(this);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(testLib);
    centralWidget()->setLayout(hLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
