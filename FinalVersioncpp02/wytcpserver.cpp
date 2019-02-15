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
    payloadSize = 4*1024;//ÿ�η���4KB
    TotalBytes = 0;//�����ܴ�С
    bytesWritten = 0;//�Ѿ��������ݴ�С
    bytesToWrite = 0;//ʣ�����ݴ�С

    //tcpServer

    ui->serverStatusLabel->setText(tr("��ѡ��Ҫ���͵��ļ�"));
    ui->progressBar->reset();
    ui->serverOpenBtn->setEnabled(true);
    ui->serverSendBtn->setEnabled(false);

    tcpServer->close();
}

//��ʼ��������,ʵ���ļ���С����Ϣ�ķ���
void WyTcpServer::sendMessage()
{
    ui->serverSendBtn->setEnabled(false);
    clientConnection = tcpServer->nextPendingConnection(); //������ȡһ�������ӵ�TcpSocket
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));//���ݳɹ����ͺ������bytesWritten()�ź�
    connect(clientConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    ui->serverStatusLabel->setText(tr("��ʼ�����ļ� %1 ��").arg(theFileName));
    localFile = new QFile(fileName);

    if(!localFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this,tr("Ӧ�ó���"),tr("�޷���ȡ�ļ� %1��\n %2").arg(fileName).arg(localFile->errorString()));
        return;

    }
    TotalBytes = localFile->size();//�ļ��ܴ�С
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);
    time.start();
    QString currentFile = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    //���͸�ʽ
    sendOut<<qint64(0)<<qint64(0)<<currentFile;
     //����д���ܴ�С��Ϣ�ռ䣬�ļ�����С��Ϣ�ռ䣬�ļ���
    TotalBytes += outBlock.size();
     //������ܴ�С���ļ�����С����Ϣ��ʵ���ļ���С���ܺ�
    sendOut.device()->seek(0);
    sendOut<<TotalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));
     //����outBolock�Ŀ�ʼ����ʵ�ʵĴ�С��Ϣ��������qint64(0)�ռ�
    bytesToWrite = TotalBytes - clientConnection->write(outBlock);//�״δ����ʣ�����ݵĴ�С
    //������ͷ���ݺ�ʣ�����ݵĴ�С
   // ui->clientStatusLabel->setText(tr("������"));
    outBlock.resize(0);


}

//���½�������ʵ���ļ��Ĵ���
void WyTcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();//�ڴ�����ļ�ʱʹ���治�ᶳ��
    //ui->serverStatusLabel->setText(tr("�ļ�ͷ�Ѵ���"));
    bytesWritten += (int)numBytes; //�Ѿ��������ݵĴ�С
    if(bytesToWrite > 0)//����Ѿ�����������
    {
        //ÿ�η���loadSize��С�����ݣ���������Ϊ4KB�����ʣ������ݲ���4KB���ͷ���ʣ�����ݵĴ�С
        outBlock = localFile->read(qMin(bytesToWrite,payloadSize));
        //������һ�����ݺ�ʣ�����ݵĴ�С
        bytesToWrite -= (int)clientConnection->write(outBlock);
        //��շ��ͻ�����
        outBlock.resize(0);
    }else{
        //���û�з����κ����ݣ���ر��ļ�
        localFile->close();
    }

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten/useTime;
    ui->serverStatusLabel->setText(tr("�ѷ��� %1MB (%2MB/s) "
                   "\n��%3MB ����ʱ:%4��\n����ʣ��ʱ�䣺%5��")
                   .arg(bytesWritten / (1024*1024))
                   .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                   .arg(TotalBytes / (1024 * 1024))
                   .arg(useTime/1000, 0, 'f', 0)
                   .arg(TotalBytes/speed/1000 - useTime/1000, 0, 'f', 0));
    if(bytesWritten == TotalBytes)//�������
    {
        localFile->close();
        tcpServer->close();
        ui->serverStatusLabel->setText(tr("�����ļ�%1�ɹ�").arg(theFileName));
        localFile->close();
        bytesWritten = 0; // clear fot next send
        bytesToWrite = 0;
        TotalBytes = 0;
       //tcpSocket->close();
    }
}

//�򿪰�ť
void WyTcpServer::on_serverOpenBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
        ui->serverStatusLabel->setText(tr("Ҫ���͵��ļ�Ϊ %1").arg(theFileName));
        ui->serverSendBtn->setEnabled(true);
        ui->serverOpenBtn->setEnabled(false);
    }
}

//���Ͱ�ť
void WyTcpServer::on_serverSendBtn_clicked()
{
    if(!tcpServer->listen(QHostAddress::Any,tcpPort))//��ʼ����
    {
        qDebug()<<tcpServer->errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText(tr("�ȴ��Է����ա�����������"));
    emit sendFileName(theFileName);
}

//�رհ�ť
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

//���ܾ�
void WyTcpServer::refused()
{
    tcpServer->close();
    ui->serverStatusLabel->setText(tr("�Է��ܾ����գ�����"));
}


void WyTcpServer::closeEvent(QCloseEvent *)
{
    on_serverCloseBtn_clicked();
}
