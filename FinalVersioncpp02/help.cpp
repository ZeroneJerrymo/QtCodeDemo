#include "help.h"
#include "ui_help.h"
#include"sysbutton.h"
#include<QSettings>
#include<QMessageBox>
#include<QPainter>
help::help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{

    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    btnMin=new sysButton("sys_button_min.png",tr("最小化"));
    connect(btnMin,SIGNAL(clicked()),this,SLOT(showMin()));
    btnClose=new sysButton("sys_button_close.png",tr("关闭"));
    connect(btnClose,SIGNAL(clicked()),this,SLOT(showclose()));//关闭 记者要发送离开信息

    ui->horizontalLayout->addStretch();
    ui->horizontalLayout->addWidget(btnMin);
    ui->horizontalLayout->addWidget(btnClose);
    ui->horizontalLayout->setSpacing(0);
    ui->horizontalLayout->setContentsMargins(0,0,0,0);
    timer=new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(TimeOut()));

    timer->start(500);
    temp_str="Thank classmates with the help of the teachers and friends, and in this sincere thanks！";
    pos1=0;
}

void help::TimeOut()
{
  if(pos1>temp_str.length())

    pos1=0;
    coder=QTextCodec::codecForName("utf-8");
    //ui->lineEdit->setText(temp_str.substr(pos).c_str());
    pos1++;

}
help::~help()
{
    delete ui;
}
void help::showMin()
{
    showMinimized();
}
void help::showclose()
{
    this->close();
}

void help::mousePressEvent(QMouseEvent *e)
{

     this->windowPos = this->pos();
     this->mousePos = e->globalPos();
     this->dPos = mousePos - windowPos;
}

void help::mouseMoveEvent(QMouseEvent *e)
{

     this->move(e->globalPos() - this->dPos);
}
void help::mouseReleaseEvent(QMouseEvent *e)
{
    if(isMove)
        isMove=false;
}
