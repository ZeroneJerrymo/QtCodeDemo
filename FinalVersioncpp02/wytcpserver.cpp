#include "wytcpserver.h"
#include "ui_wytcpserver.h"

#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QDataStream>

WyTcpServer::WyTcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WyTcpServer)
{
    ui->setupUi(this);
    setFixedSize(350,180);

    tcpPort = 45454;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(sendMessage()));

    //connect(tcpServer,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    //connect(tcpServer,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    initServer();
}


WyTcpServer::~WyTcpServer()
{
    delete ui;
}

void WyTcpServer::initServer()
{
    payloadSize = 4*1024;//每次发送4KB
    TotalBytes = 0;//数据总大小
    bytesWritten = 0;//已经发送数据大小
    bytesToWrite = 0;//剩余数据大小

    //tcpServer

    ui->serverStatusLabel->setText(tr("请选择要传送的文件"));
    ui->progressBar->reset();
    ui->serverOpenBtn->setEnabled(true);
    ui->serverSendBtn->setEnabled(false);

    tcpServer->close();
}

//开始发送数据,实现文件大小等信息的发送
void WyTcpServer::sendMessage()
{
    ui->serverSendBtn->setEnabled(false);
    clientConnection = tcpServer->nextPendingConnection(); //用来获取一个已连接的TcpSocket
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));//数据成功发送后产生的bytesWritten()信号
    connect(clientConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    ui->serverStatusLabel->setText(tr("开始传送文件 %1 ！").arg(theFileName));
    localFile = new QFile(fileName);

    if(!localFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1：\n %2").arg(fileName).arg(localFile->errorString()));
        return;

    }
    TotalBytes = localFile->size();//文件总大小
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);
    time.start();
    QString currentFile = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    //发送格式
    sendOut<<qint64(0)<<qint64(0)<<currentFile;
     //依次写入总大小信息空间，文件名大小信息空间，文件名
    TotalBytes += outBlock.size();
     //这里的总大小是文件名大小等信息和实际文件大小的总和
    sendOut.device()->seek(0);
    sendOut<<TotalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));
     //返回outBolock的开始，用实际的大小信息代替两个qint64(0)空间
    bytesToWrite = TotalBytes - clientConnection->write(outBlock);//首次传输后剩余数据的大小
    //发送完头数据后剩余数据的大小
   // ui->clientStatusLabel->setText(tr("已连接"));
    outBlock.resize(0);


}

//更新进度条，实现文件的传送
void WyTcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();//在传输大文件时使界面不会冻结
    //ui->serverStatusLabel->setText(tr("文件头已传送"));
    bytesWritten += (int)numBytes; //已经发送数据的大小
    if(bytesToWrite > 0)//如果已经发送了数据
    {
        //每次发送loadSize大小的数据，这里设置为4KB，如果剩余的数据不足4KB，就发送剩余数据的大小
        outBlock = localFile->read(qMin(bytesToWrite,payloadSize));
        //发送完一次数据后还剩余数据的大小
        bytesToWrite -= (int)clientConnection->write(outBlock);
        //清空发送缓冲区
        outBlock.resize(0);
    }else{
        //如果没有发送任何数据，则关闭文件
        localFile->close();
    }

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten/useTime;
    ui->serverStatusLabel->setText(tr("已发送 %1MB (%2MB/s) "
                   "\n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                   .arg(bytesWritten / (1024*1024))
                   .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                   .arg(TotalBytes / (1024 * 1024))
                   .arg(useTime/1000, 0, 'f', 0)
                   .arg(TotalBytes/speed/1000 - useTime/1000, 0, 'f', 0));
    if(bytesWritten == TotalBytes)//发送完毕
    {
        localFile->close();
        tcpServer->close();
        ui->serverStatusLabel->setText(tr("传送文件%1成功").arg(theFileName));
        localFile->close();
        bytesWritten = 0; // clear fot next send
        bytesToWrite = 0;
        TotalBytes = 0;
       //tcpSocket->close();
    }
}

//打开按钮
void WyTcpServer::on_serverOpenBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
        ui->serverStatusLabel->setText(tr("要传送的文件为 %1").arg(theFileName));
        ui->serverSendBtn->setEnabled(true);
        ui->serverOpenBtn->setEnabled(false);
    }
}

//发送按钮
void WyTcpServer::on_serverSendBtn_clicked()
{
    if(!tcpServer->listen(QHostAddress::Any,tcpPort))//开始监听
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText(tr("等待对方接收······"));
    emit sendFileName(theFileName);
}

//关闭按钮
void WyTcpServer::on_serverCloseBtn_clicked()
{
    if(tcpServer->isListening())
    {
        tcpServer->close();
        if(localFile->isOpen())
            localFile->close();
        clientConnection->abort();
    }
    close();
}

//被拒绝
void WyTcpServer::refused()
{
    tcpServer->close();
    ui->serverStatusLabel->setText(tr("对方拒绝接收！！！"));
}


void WyTcpServer::closeEvent(QCloseEvent *)
{
    on_serverCloseBtn_clicked();
}
