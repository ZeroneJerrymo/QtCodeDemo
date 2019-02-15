#include "dialog.h"
#include "ui_dialog.h"
#include "moviepushbutton.h"
#include <QHBoxLayout>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //    TOOTBtn*  btn = new TOOTBtn("D:\workSpace\Demo\testmap\22222.gif", "test...",this);
    //  //  btn->move(100,100);
    //    btn->setFixedSize(100,30);
    //    QHBoxLayout* hlay =new QHBoxLayout;
    //    hlay->addWidget(btn);
    //    hlay->setContentsMargins(100,100,100,100);
    //   this->setLayout(hlay);
}

Dialog::~Dialog()
{
    delete ui;
}
