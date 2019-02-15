#include "yoajiang.h"
#include "ui_yoajiang.h"

#include <QPainter>
#include <QTimer>

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    qsrand(QTime::currentTime().msec());

    ui->setupUi(this);
    pflag = false;
    Timer = new QTimer();
    Timer->setInterval(200);
    Timer ->start();
    name[0] = "one";
    name[1] = "two";
    name[2] = "three";
    name[3] = "four";
    name[4] = "five";
    QPainter qp(this);

    int num = (qrand()%5)+1;

    ui->girl->setAutoFillBackground(true);
    ui->girl->setPalette(QPalette(QColor(255,255,255)));
    ui->girl->setText(name[num-1]);
    QString imgpath = ":/image/";
    imgpath = imgpath +QString::number(num);
    img.load(imgpath);
    img = img.scaled(400,600);

    qp.drawImage(0,0,img);
    connect(Timer,SIGNAL(timeout()),this,SLOT(repaint()));
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::paintEvent(QPaintEvent *)
{
    QPainter qp(this);
    if(pflag)
    {
        int num = (qrand()%5)+1;

        ui->girl->setAutoFillBackground(true);
        ui->girl->setPalette(QPalette(QColor(255,255,255)));
        ui->girl->setText(name[num-1]);
        QString imgpath = ":/image/";
        imgpath = imgpath +QString::number(num);
        img.load(imgpath);
        img = img.scaled(400,600);
    }
    qp.drawImage(0,0,img);

}
void Dialog2::changPflag()
{
    if(((QPushButton*)sender())->objectName() == "start")
    {
        pflag = true;
    }
    if(((QPushButton*)sender())->objectName() == "stop")
    {
        pflag = false;
    }
}
