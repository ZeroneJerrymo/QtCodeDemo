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

//��ȡ�ļ���
void TcpClient::setFileName(QString fileName)
{
    qDebug()<<"setFileName";
    localFile = new QFile(fileName);
    qDebug()<<"setFileName";
}

//��ȡip��ַ
void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

//�����������������
void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,tcpPort);
    time.start();
}

//��ȡ����,���½�������ʵ���ļ��Ľ���
void TcpClient::readMessage()
{
    //ui->tcpClientStatusLabel->setText(tr("׼����ȡ����"));
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_8);

    float useTime = time.elapsed();
    //������յ�������С�ڵ���16���ֽڣ���ô�Ǹտ�ʼ�������ݣ����Ǳ���Ϊͷ�ļ���Ϣ
    if(bytesReceived<=sizeof(qint64)*2){
        //���������ܴ�С��Ϣ���ļ�����С��Ϣ
        if((tcpClient->bytesAvailable()>=sizeof(qint64)*2)&&(fileNameSize == 0))
        {
            in>>TotalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        //�����ļ������������ļ�
        if((tcpClient->bytesAvailable() >= fileNameSize)&&(fileNameSize != 0)){
            in>>fileName;
            bytesReceived += fileNameSize;
            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("Ӧ�ó���"),tr("�޷���ȡ�ļ�%2��\n%2.")
                                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }
        }else{
            return;
        }

    }
     //������յ�����С�������ݣ���ôд���ļ�
    if(bytesReceived<TotalBytes){
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    //���½�����
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived/useTime;
    ui->tcpClientStatusLabel->setText(tr("�ѽ���%1MB(%2MB/s)""\n��%3����ʱ��%4��\n����ʣ��ʱ�䣺%5��")
                                      .arg(bytesReceived/(1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(TotalBytes/(1024*1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000-useTime/1000,0,'f',0));

    //�����������ʱ
    if(bytesReceived == TotalBytes){
        localFile->close();
        tcpClient->close();
        ui->tcpClientStatusLabel->setText(tr("�����ļ� %1���").arg(fileName));
    }
}


//������
void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:break;
    default:qDebug()<<tcpClient->errorString();
    }
}

//ȡ����ť
void TcpClient::on_tcpClientCancleBtn_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen())
        localFile->close();

}

//�رհ�ť
void TcpClient::on_tcpClientCloseBtn_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen())
        localFile->close();
    close();
}

//�ر��¼�
void TcpClient::closeEvent(QCloseEvent *)
{
    on_tcpClientCloseBtn_clicked();
}
