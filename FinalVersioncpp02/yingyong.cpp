#include "yingyong.h"
#include "ui_yingyong.h"

add::add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add)
{
    ui->setupUi(this);
    createdatedir();
    createpathdir();
     this->setStyleSheet("background-image:url(:/image/6.jpg);");
    ui->tabWidget->setStyleSheet("background-image:url(:/image/6.jpg);");
    //QObject::connect(ui->pushButton_yaojiang,SIGNAL(clicked()),this,SLOT(on_pushButton_yaojiang_clicked()));
    //QObject::connect(ui->pushButton_14,SIGNAL(clicked()),this,SLOT(on_pushButton_14_clicked()));
    //QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    //QObject::connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(on_pushButton_6_clicked()));
}
 //QString add::addr[0]=null;
// QString add::addr[1]=null;
// QString add::addr[2]=null;
 //QString add::addr[3]=null;
add::~add()
{
    delete ui;
}

//创建本地软件打开路径文件夹
void add::createpathdir()
{
   QDir *temp = new QDir;
   bool exist = temp->exists("path");
   if(exist)
       return;
   else
   {
      temp->mkdir("path");
   }
}

//创建备忘事件路径文件夹
void add::createdatedir()
{
   QDir *temp = new QDir;
   bool exist = temp->exists("date");
   if(exist)
       return;
   else
   {
      temp->mkdir("date");
   }
}

//打开腾讯网
void add::on_pushButton_qqcom_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.qq.com"));
    return;
}

//打开淘宝网
void add::on_pushButton_taobao_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.taobao.com"));
    return;
}

//打开新浪网
void add::on_pushButton_sina_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.sina.com"));
    return;
}

//打开百度网
void add::on_pushButton_baidu_clicked()
{
     QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
     return;
}

//打开备忘录
void add::on_pushButton_NotePad_clicked()
{
    Widget2 *widget=new Widget2;
    widget->show();
}

//打开IE浏览器
void add::on_pushButton_IE_clicked()
{

    QString str="C:\\Program Files\\Internet Explorer\\iexplore.exe";
    QProcess *process=new QProcess;
    process->startDetached(str,QStringList(str));
}

//打开QQ
void add::on_pushButton_QQ_clicked()
{

    QString filename="path/pathQQ.txt";
    QString str;
    QFileInfo fileinfo(filename);
    if(!fileinfo.exists())
    {
        QFile file(filename);


        str=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
        QProcess *process=new QProcess;

        process->startDetached(str,QStringList(str));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));

        if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream in(&file);
        in<<str;
        file.close();
        return ;

    }else{
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream out(&file);
        QString curpath;
        while(!out.atEnd()){
            curpath=out.readLine();
        }
        file.close();
        QProcess *process=new QProcess;

        process->startDetached(curpath,QStringList(curpath));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));
       return ;


    }



    /*QString curpath;
    if(!propath->contains("1"))
    {
     str=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
    propath->insert("1",str);
   }else{
        QMap<QString,QString>::const_iterator i =propath->find("1");
        while (i != propath->end() && i.key() != "1") {

               i++;
        }
        curpath=i.value();
    }*/
    // QDesktopServices::openUrl(QUrl("file:///C:/Documents and Settings/All Users/Desktop", QUrl::TolerantMode));

    //QString str="C:\\Program Files\\Tencent\\QQ\\QQProtect\\Bin\\QQProtect.exe";

}

//打开QT
void add::on_pushButton_QT_clicked()
{
    QString filename="path/pathQt.txt";
    QString str;
    QFileInfo fileinfo(filename);
    if(!fileinfo.exists())
    {
        QFile file(filename);


        str=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
        QProcess *process=new QProcess;

        process->startDetached(str,QStringList(str));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));

        if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream in(&file);
        in<<str;
        file.close();
        return ;

    }else{
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream out(&file);
        QString curpath;
        while(!out.atEnd()){
            curpath=out.readLine();
        }
        file.close();
        QProcess *process=new QProcess;

        process->startDetached(curpath,QStringList(curpath));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));
       return ;


    }
}

//打开播放器
void add::on_pushButton_DVD_clicked()
{

    QString filename="path/path-player.txt";
    QString str;
    QFileInfo fileinfo(filename);
    if(!fileinfo.exists())
    {
        QFile file(filename);


        str=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
        QProcess *process=new QProcess;

        process->startDetached(str,QStringList(str));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));

        if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream in(&file);
        in<<str;
        file.close();
        return ;

    }else{
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
           {
              QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
           }
        QTextStream out(&file);
        QString curpath;
        while(!out.atEnd()){
            curpath=out.readLine();
        }
        file.close();
        QProcess *process=new QProcess;

        process->startDetached(curpath,QStringList(curpath));
       //QDesktopServices::openUrl(QUrl("file:///C:\Program Files\Tencent\QQ\QQProtect\Bin\QQProtect", QUrl::TolerantMode));
       return ;


    }
}

//打开贪吃蛇游戏
void add::on_pushButton_snake_clicked()
{
   SnakeGame *dialog=new SnakeGame;
   dialog->show();
}

//打开摇奖游戏
void add::on_pushButton_yaojiang_clicked()
{
    Dialog2 *dialog=new Dialog2;
    dialog->show();
}
