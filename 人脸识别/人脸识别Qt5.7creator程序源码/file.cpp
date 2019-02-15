#include "file.h"
#include <QMessageBox>
#include <QDebug>

MyFILE::MyFILE(QObject *parent):QObject(parent)
{

}

void MyFILE::getManLabel()
{
    QString QStrLine[10];
    QFile file("./Data/people.txt");
    QTextStream in(&file);
    in.setCodec("UTF-8");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox about;
        about.setText(tr("people.txt打开失败"));
        about.exec();
        return;
    }
    int i=0;
    while(!in.atEnd())
    {
        QByteArray Line=file.readLine();
        QStrLine[i]=Line;
        //qDebug()<<"QStrLine[i]:"<<QStrLine[i];
        //提取数字和名字
        QString Num;
        QString name;
        for(int j=0;j<QStrLine[i].length();j++)
        {
            if(QStrLine[i][j]>='0'&& QStrLine[i][j]<='9')
            {
                Num.append(QStrLine[i][j]);
            }
            if(QStrLine[i][j]!=' '&& (QStrLine[i][j]<='0' || QStrLine[i][j]>='9'))
            {
                name.append(QStrLine[i][j]);
            }
        }
        whoLable[i]=Num.toInt();
        who[i]=name;
        //qDebug()<<name;
        //qDebug()<<"whoLable[i]:"<<whoLable[i];
        i++;
    }
    file.close();
}

void MyFILE::MakecsvFile()
{
    QDir csvFile("./Data/at.txt");
    QString csvPath=csvFile.absolutePath();
    QString csvFilePath=csvPath;
    csvPath.chop(6);
    QString path=csvPath+QString::number(MaxNumAboutPeople,10)+"/";
    for(int i=0;i<10;i++)
    {
        QString filepath=path;
        filepath.append(QString::number(i,10));
        filepath.append(".jpg;");
        filepath.append(QString::number(MaxNumAboutPeople,10));
        this->AddPeople(csvFilePath,filepath);
    }
}

void MyFILE::CreateFile(QString fileName)
{
    PicFile=new QDir;
    QString path="Data\\"+fileName;
    if(PicFile->exists(path))
    {
        QMessageBox about;
        about.setText(tr("文件夹创建失败"));
        about.exec();
    }
    else
    {
        if(PicFile->mkdir(path))
        {
            QMessageBox about;
            about.setText(tr("文件夹创建成功"));
            about.exec();
        }
    }
}

void MyFILE::AddPeople(QString path,QString text)
{
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        QMessageBox about;
        about.setText(tr("添加人员时文件打开失败"));
        about.exec();
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    in<<text<<"\r\n";
    file.close();
}

int MyFILE::GetMaxNum(QString path)
{
    QString str[128];
    int i=0;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox about;
        about.setText(tr("获取编号时文件打开失败"));
        about.exec();
        return -1;
    }
    else
    {
        while(!file.atEnd())
        {
            QByteArray Line=file.readLine();
            str[i]=Line;
            //qDebug()<<str[i].toStdString().c_str()<<endl;
            i++;
        }
        MaxNumAboutPeople=i;
        file.close();
    }
    return i;
}
