#include "set.h"
#include "ui_set.h"
#include<QBitmap>
#include<QPainter>
#include<QSettings>
#include<QMessageBox>
#include<QDebug>
#include<QDir>
#include<QButtonGroup>
#include"sysbutton.h"
#include<QWidget>
#include<QDialog>
#include"widget.h"

set::set(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::set)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(close()));

    this->setWindowIcon(QIcon(":img/qq.ico"));
    setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);

    p.setRenderHint(QPainter::Antialiasing);    //�����
    int arcR = 10;    //����
    QRect rect = this->rect();
    QPainterPath path;
    //��ʱ��
    path.moveTo(arcR, 0);
    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
    path.lineTo(0, rect.height());
    path.lineTo(rect.width(), rect.height());
    path.lineTo(rect.width(), arcR);
    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
    path.lineTo(arcR, 0);
    p.drawPath(path);
    p.fillPath(path, QBrush(Qt::red)); //arm��windowsƽ̨û�����д��뽫��ʾһ��͸���ĿտյĿ�
    setMask(bmp);
    //==========ʵ���ϱ߽�Բ��==========
    btnMin=new sysButton("sys_button_min.png",tr("��С��"));
    connect(btnMin,SIGNAL(clicked()),this,SLOT(showMin()));
    btnClose=new sysButton("sys_button_close.png",tr("�ر�"));
    connect(btnClose,SIGNAL(clicked()),this,SLOT(showclose()));//�ر� ����Ҫ�����뿪��Ϣ

    ui->Mian_Layout->addStretch();
    ui->Mian_Layout->addWidget(btnMin);
    ui->Mian_Layout->addWidget(btnClose);
    ui->Mian_Layout->setSpacing(0);
    ui->Mian_Layout->setContentsMargins(0,0,0,0);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(submit_slot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(calcel_slot()));

    QSettings settings("info.ini", QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
    ui->name->setText(settings.value("infomation/User_name").toString());
//    ui->sex->setText(settings.value("infomation/User_sex").toString());
    ui->sign->setText(settings.value("infomation/User_sign").toString());
    Icon_Init();
    photo_Init();
    qDebug()<<"here"<<ui->Head_box->currentIndex()<<endl;
}


set::~set()
{
    delete ui;
}


void set::photo_Init()
{
    QSettings settings("info.ini", QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
    QDir dir(":img/xingxiang");//����Ĭ��·��
    if (!dir.isReadable())                                                //�Ƿ��·���ɶ�
    {
        QMessageBox::critical(0, QString::fromUtf8("����"), QString::fromUtf8("ͷ���ļ�·������ȷ"));
    }
    int myHeadIndex = 0;
    photoList = dir.entryList(QDir::Files);                                //����ļ��е������ļ�
    QString now_photo = settings.value("information/User_photo").toString();

    for (int i=0; i<photoList.count(); i++)
    {
            QString fileName = dir.filePath(photoList.at(i));                  //�����ļ����·����
            if (fileName == now_photo)                                           //��¼��ǰ�û�ͷ������
            {
                    myHeadIndex = i;
            }

            ui->photo_box->addItem(QIcon(fileName), NULL);  //��ӽ��б��
            ui->photo_box->setIconSize(QSize(80,80));
    }

    ui->photo_box->setCurrentIndex(myHeadIndex);                                //��ʾ��ǰ����ͷ��

}
void set::Icon_Init()
{
    QSettings settings("info.ini", QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
    QDir dir(":img/head_icon");//����Ĭ��·��
    if (!dir.isReadable())                                                //�Ƿ��·���ɶ�
    {
        QMessageBox::critical(0, QString::fromUtf8("����"), QString::fromUtf8("ͷ���ļ�·������ȷ"));
    }
    int myHeadIndex = 0;
    headList = dir.entryList(QDir::Files);                                //����ļ��е������ļ�
    QString now_head_icon = settings.value("information/User_icon").toString();

    for (int i=0; i<headList.count(); i++)
    {
            QString fileName = dir.filePath(headList.at(i));                  //�����ļ����·����
            if (fileName == now_head_icon)                                           //��¼��ǰ�û�ͷ������
            {
                    myHeadIndex = i;
            }

            ui->Head_box->addItem(QIcon(fileName), NULL);
            ui->Head_box->setIconSize(QSize(80,80));//��ӽ��б��
    }

    ui->Head_box->setCurrentIndex(myHeadIndex);                                //��ʾ��ǰ����ͷ��

}
void set::submit_slot()
{
    QSettings settings("info.ini", QSettings::IniFormat); // ��ǰĿ¼��INI�ļ�
    QString name_ini = ui->name->text();
//    QString sex_ini = ui->sex->text();
    QString sign_ini = ui->sign->text();
    settings.beginGroup("infomation");
    settings.setValue("User_name",name_ini);
//    settings.setValue("User_sex",sex_ini);
    settings.setValue("User_sign",sign_ini);//�洢�������ļ���
    QDir dir(":img/head_icon");
    if (!dir.isReadable())                                                //�Ƿ��·���ɶ�
    {
        QMessageBox::critical(0, QString::fromUtf8("����"), QString::fromUtf8("ͷ���ļ�·������ȷ"));
    }

    int index = ui->Head_box->currentIndex();                                 //���ѡ��ͷ������
    QString head = dir.filePath(headList.at(index));
    settings.setValue("User_icon",head);

    QDir dir_photo(":img/xingxiang");
    if(!dir_photo.isReadable())
    {
        QMessageBox::critical(0, QString::fromUtf8("����"), QString::fromUtf8("ͷ���ļ�·������ȷ"));
    }
    int photo_index = ui->photo_box->currentIndex();
    QString photo = dir_photo.filePath(photoList.at(photo_index));
    settings.setValue("User_photo",photo);//�����û�������Ƭ
    QSettings check("info.ini", QSettings::IniFormat);//�������Ƿ�ɹ�
    QString name_che = check.value("infomation/User_name").toString();
    QString sex_che = check.value("infomation/User_sex").toString();
    QString sign_che = check.value("infomation/User_sign").toString();
    QString icon_che = check.value("infomation/User_icon").toString();
    QString photo_che = check.value("infomation/User_photo").toString();

    if((name_che == name_ini ) &&(name_che == name_ini )&& (sign_che == sign_ini)  &&(icon_che == head) && (photo_che == photo))
    {
        QMessageBox::information(0,"congratulations","save successfully");
    }
    else
    {
         QMessageBox::information(0,"false","save failed");
    }
    this->close();
}
void set::calcel_slot()
{
    this->close();
}

void set::mousePressEvent(QMouseEvent *e)
{

     this->windowPos = this->pos();
     this->mousePos = e->globalPos();
     this->dPos = mousePos - windowPos;
}

void set::mouseMoveEvent(QMouseEvent *e)
{

    this->move(e->globalPos() - this->dPos);
}
void set::mouseReleaseEvent(QMouseEvent *e)
{
    if(isMove)
        isMove=false;
}

void set::showMin()
{
    showMinimized();
}
void set::showclose()
{
    this->close();
}
