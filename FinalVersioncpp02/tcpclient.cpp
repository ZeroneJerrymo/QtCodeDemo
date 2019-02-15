#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>
TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    setFixedSize(350,180);

    TotalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    tcpClient = new QTcpSocket(this);
    tcpPort = 45454;

    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(readMessage()));
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),
           this,SLOT(displayError(QAbstractSocket::SocketError)));
}

TcpClient::~TcpClient()
{
    delete ui;
}

//获取文件名
void TcpClient::setFileName(QString fileName)
{
    qDebug()<<"setFileName";
    localFile = new QFile(fileName);
    qDebug()<<"setFileName";
}

//获取ip地址
void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

//设置与服务器的连接
void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,tcpPort);
    time.start();
}

//读取数据,更新进度条，实现文件的接收
void TcpClient::readMessage()
{
    //ui->tcpClientStatusLabel->setText(tr("准备读取数据"));
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_8);

    float useTime = time.elapsed();
    //如果接收到的数据小于等于16个字节，那么是刚开始接收数据，我们保存为头文件信息
    if(bytesReceived<=sizeof(qint64)*2){
        //接收数据总大小信息和文件名大小信息
        if((tcpClient->bytesAvailable()>=sizeof(qint64)*2)&&(fileNameSize == 0))
        {
            in>>TotalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        //接收文件名，并建立文件
        if((tcpClient->bytesAvailable() >= fileNameSize)&&(fileNameSize != 0)){
            in>>fileName;
            bytesReceived += fileNameSize;
            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件%2：\n%2.")
                                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }
        }else{
            return;
        }

    }
     //如果接收的数据小于总数据，那么写入文件
    if(bytesReceived<TotalBytes){
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    //更新进度条
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived/useTime;
    ui->tcpClientStatusLabel->setText(tr("已接收%1MB(%2MB/s)""\n共%3已用时：%4秒\n估计剩余时间：%5秒")
                                      .arg(bytesReceived/(1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(TotalBytes/(1024*1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000-useTime/1000,0,'f',0));

    //接收数据完成时
    if(bytesReceived == TotalBytes){
        localFile->close();
        tcpClient->close();
        ui->tcpClientStatusLabel->setText(tr("接收文件 %1完毕").arg(fileName));
    }
}


//错误处理
void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:break;
    default:qDebug()<<tcpClient->errorString();
    }
}

//取消按钮
void TcpClient::on_tcpClientCancleBtn_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen())
        localFile->close();

}

//关闭按钮
void TcpClient::on_tcpClientCloseBtn_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen())
        localFile->close();
    close();
}

//关闭事件
void TcpClient::closeEvent(QCloseEvent *)
{
    on_tcpClientCloseBtn_clicked();
}
