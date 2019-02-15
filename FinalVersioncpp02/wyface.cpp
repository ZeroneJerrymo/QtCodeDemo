#include "ui_wyface.h"
#include "wyface.h"
#include <QString>
#include <QChar>
#include <QDebug>

WyFace::WyFace(QWidget *parent):
    QDialog(parent)

{
    ui = new Ui::WyFace();
    ui->setupUi(this);
    //this->setWindowFlags(windowFlags()|Qt::FramelessWindowHint|Qt::WindowTitleHint);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QObject::connect(ui->toolButton_1, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_2, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_3, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_4, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_5, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_6, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_7, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_8, SIGNAL(clicked()), this, SLOT(clickFace()));
    QObject::connect(ui->toolButton_9, SIGNAL(clicked()), this, SLOT(clickFace()));
}

WyFace::~WyFace()
{
    delete ui;
}

void WyFace::clickFace()
{
    QString str = sender()->objectName();
    QChar ch = str[str.length()-1];
    qDebug()<<ch;
    QString pth = "/images/face/0";
    pth += ch;
    pth += ".png";
    this->pth = pth;

    qDebug()<<pth;
}
QString WyFace::getPth()
{
    return pth;
}
void WyFace::on_toolButton_1_clicked()
{
    close();
}
void WyFace::on_toolButton_2_clicked()
{
    close();
}
void WyFace::on_toolButton_3_clicked()
{
    close();
}
void WyFace::on_toolButton_4_clicked()
{
    close();
}
void WyFace::on_toolButton_5_clicked()
{
    close();
}
void WyFace::on_toolButton_6_clicked()
{
    close();
}
void WyFace::on_toolButton_7_clicked()
{
    close();
}
void WyFace::on_toolButton_8_clicked()
{
    close();
}
void WyFace::on_toolButton_9_clicked()
{
    close();
}
