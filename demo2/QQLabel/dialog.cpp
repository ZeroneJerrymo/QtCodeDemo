#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    label[0] = new GLabel(this,GLabel::Me);
    label[0]->setGeometry(05,10,100,66);
    label[0]->setOurText(tr("���!"));
    label[0]->show();

    label[1] = new GLabel(this,GLabel::She);
    label[1]->setGeometry(5,label[0]->y()+label[0]->height(),100,66);
    label[1]->setOurText(QString::fromLocal8Bit( "���!"));
    label[1]->show();

    label[2] = new GLabel(this,GLabel::Me);
    label[2]->setGeometry(5,label[1]->y()+label[1]->height(),100,66);
    label[2]->setOurText(QString::fromLocal8Bit("���Ǻ��������������"));
    label[2]->show();

    label[3] = new GLabel(this,GLabel::She);
    label[3]->setGeometry(5,label[2]->y()+label[2]->height(),100,66);
    label[3]->setOurText(tr("��"));
    label[3]->show();

    label[4] = new GLabel(this,GLabel::Me);
    label[4]->setGeometry(5,label[3]->y()+label[3]->height(),100,66);
    label[4]->setOurText(tr("���Ǻ������ļ�����ǵ��𣿺�������һ������Ϧ�����£����������Ҳ��Һ���˵�����㾭����ʱ���𸡶��ҵķ�"));
    label[4]->show();

    label[5] = new GLabel(this,GLabel::She);
    label[5]->setGeometry(5,label[4]->y()+label[4]->height(),100,66);
    label[5]->setOurText(tr("���ӻ��ǻ�Ƶģ�ѩҲ���ٴ�Ⱦ���������硣����"));
    label[5]->show();
}

Dialog::~Dialog()
{
    delete ui;
}
