#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CProfessionalWordDbWgt.h"
#include <QVBoxLayout>
#include <QTextEdit>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pshowWiget = new CProfessionalWordDbWgt();
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(slot_setspeech()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_setspeech()
{
    pshowWiget->setSpeedWord(ui->textEdit->toPlainText());
}

void MainWindow::on_pushButton_clicked()
{
    pshowWiget->show();

}
