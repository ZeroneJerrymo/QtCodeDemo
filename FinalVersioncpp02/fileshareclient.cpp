#include "fileshareclient.h"
#include "ui_fileshareclient.h"

FileShareClient::FileShareClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileShareClient)
{
    ui->setupUi(this);
    TotalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;
    tcpClient = new QTcpSocket();
    tcpPort = 6666;
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readFile()));
}

FileShareClient::~FileShareClient()
{
    delete ui;
}

void FileShareClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

void FileShareClient::setFileName(QString fileName)
{
    localFile = new QFile(fileName);
}

void FileShareClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress, tcpPort);
    time.start();
}

void FileShareClient::readFile()
{
    qDebug()<<"start to receieve file";
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_8);

    if (bytesReceived <= sizeof(qint64)*2) {
        if ((tcpClient->bytesAvailable()
             >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            in>>TotalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tcpClient->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            in>>fileName;
            bytesReceived +=fileNameSize;

            if(!localFile->open(QFile::WriteOnly)){
                qDebug()<<tr("cannot read file")<<fileName;
//                QMessageBox::warning(this,("Application"),("cann't read file %1:\n%2.")
//                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }
    if (bytesReceived < TotalBytes) {
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    if(bytesReceived == TotalBytes)
    {
        qDebug()<<tr("receive file successfully");
        localFile->close();
        tcpClient->close();
    }
}
