#include "fileshareserver.h"
#include "ui_fileshareserver.h"

FileShareServer::FileShareServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileShareServer)
{
    ui->setupUi(this);
    udpSend = new QUdpSocket(this);
    udpReceive = new QUdpSocket(this);
    udpReceive->bind(9090,QUdpSocket::ShareAddress);
    connect(udpReceive,SIGNAL(readyRead()),this,SLOT(receiveMessage()));
    sendSignal(New);
    tcpPort = 6666;
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendFile()));
//    connect(this, SIGNAL(sendFileName(QString)), this, SLOT(getFileName(QString)));

}

FileShareServer::~FileShareServer()
{
//    sendSignal(Left);
    delete ui;
}




void FileShareServer::on_UpLoadButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
        ui->CancelButton->setEnabled(true);
        ui->DownLoadButton->setEnabled(true);
        UpLoadTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        UpLoadUserName = getUserName();
//        newFile(theFileName, UpLoadTime, UpLoadUserName);
        sendSignal(File);
        Fpackage.FileName = theFileName;
        Fpackage.UpLoadTime = UpLoadTime;
        Fpackage.UpLoadUserName = UpLoadUserName;
        FpackageList.push_back(Fpackage);
    }

}

QString FileShareServer::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list) {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}


void FileShareServer::newFile(QString FileName, QString UpLoadTime, QString UpLoadUserName, QString UserIp)
{
    bool isEmpty = ui->userTableWidget->findItems(FileName, Qt::MatchExactly).isEmpty();
    if (isEmpty) {
        QTableWidgetItem *FName = new QTableWidgetItem(FileName);
        QTableWidgetItem *ULdTime = new QTableWidgetItem(UpLoadTime);
        QTableWidgetItem *ULUserName = new QTableWidgetItem(UpLoadUserName);
        QTableWidgetItem *USERIp = new QTableWidgetItem(UserIp);

        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0,0,FName);
        ui->userTableWidget->setItem(0,1,ULdTime);
        ui->userTableWidget->setItem(0,2,ULUserName);
        ui->userTableWidget->setItem(0,3,USERIp);
//        ui->userNumLabel->setText(tr("Online Number:%1").arg(ui->userTableWidget->rowCount()));
//        sendMessage(NewParticipant);
    }
//    else
//    {
//        QMessageBox::information(this,tr("Waring"),tr("File %1 existed!").arg(FileName),0);
//    }
}

QString FileShareServer::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*"
                 << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
    foreach (QString string, envVariables) {
        int index = environment.indexOf(QRegExp(string));
        if (index != -1) {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2) {
                return stringList.at(1);
                break;
            }
        }
    }
    return "unknown";
}

void FileShareServer::sendSignal(MessageShareType type ,QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    QString address = getIP();
    QString time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");
    out << type ;

    switch(type)
    {
    case New :
        out << address;
        break;

    case File :
        out << theFileName << time << getUserName() << address;
        break;

    case Left:
//        for(std::vector<FilePackage>::iterator iter = FpackageList.begin(); iter != FpackageList.end(); iter++)
//        {
//             fileName = iter->FileName;
//             QByteArray data;
//             QDataStream out(&data,QIODevice::WriteOnly);
//             out << fileName;
//             udpSend->writeDatagram(data.data(),data.length(),QHostAddress::Broadcast,9090);
//        }
        break;

    case cancel:
        out << fileName;
        break;

    case FB:
    {
        int trow = ui->userTableWidget->currentRow();
        QString tclientAddress = ui->userTableWidget->item(trow, 3)->text();
        theFileName = ui->userTableWidget->item(trow,0)->text();
        out<<tclientAddress<<address;
    }
        break;

    case FN:
        out <<address << clientAddress <<theFileName;
        break;


    }
    udpSend->writeDatagram(data.data(),data.length(),QHostAddress::Broadcast,9090);


}


void FileShareServer::receiveMessage()
{
    while(udpReceive->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udpReceive->pendingDatagramSize());
        udpReceive->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        qDebug()<<messageType;
        qDebug()<<theFileName;
        QString fileName,  UpLoadTime,  UpLoadUserName, UserIp;
        switch(messageType)
        {
        case New:
            for(std::vector<FilePackage>::iterator iter = FpackageList.begin(); iter != FpackageList.end(); iter++)
            {
                 fileName = iter->FileName;
                 UpLoadTime = iter->UpLoadTime;
                 UpLoadUserName = iter->UpLoadUserName;
                 UserIp = iter->UserIp;
                 QByteArray data;
                 QDataStream out(&data,QIODevice::WriteOnly);
                 MessageShareType type = File;
                 out << type;
                 out << fileName << UpLoadTime << UpLoadUserName <<UserIp;
                 udpSend->writeDatagram(data.data(),data.length(),QHostAddress::Broadcast,9090);
            }
            break;

        case File: {
            in >> fileName >> UpLoadTime >> UpLoadUserName >>UserIp;
            qDebug()<<fileName;
            newFile(fileName,UpLoadTime,UpLoadUserName,UserIp);
        }
            break;
        case Left:
//            in >> fileName;
//            QString temp = fileName;
//            while(!temp.compare(""))
//            {
//                int rowNum = ui->userTableWidget->findItems(fileName, Qt::MatchExactly).first()->row();
//                ui->userTableWidget->removeRow(rowNum);
//            }
            break;
        case cancel:
        {
            in >> fileName;
            int rowNum = ui->userTableWidget->findItems(fileName, Qt::MatchExactly).first()->row();
            ui->userTableWidget->removeRow(rowNum);
            for(std::vector<FilePackage>::iterator iter = FpackageList.begin(); iter != FpackageList.end(); iter++)
            {
                if(fileName.compare(iter->FileName)==0)
                {
                    FpackageList.erase(iter);
                }
            }
        }
            break;

        case FB:
        {
            QString address;
            in >> address >> clientAddress;
            if(getIP()==address)
            {
                sendSignal(FN);
            }
        }
            break;

        case FN:
        {
            QString fclientAddress, fileName;
            in >> fclientAddress >> UserIp >> fileName;
            hasPendingFile(UserIp, fclientAddress, fileName);
        }
            break;

        }
    }
}

void FileShareServer::sendFile()
{
    qDebug()<<tr("send the head of file");
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));//数据成功发送后产生的bytesWritten()信号
    //connect(clientConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

    localFile = new QFile(theFileName);
//    if(!localFile->open((QFile::ReadOnly))){
//        QMessageBox::warning(this, tr("Application"), tr("cann't read file %1:\n%2")
//                             .arg(theFileName).arg(localFile->errorString()));
//        return;
//    }
    TotalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_8);
    //time.start();  // 开始计时
    QString currentFile = theFileName.right(theFileName.size()
                                         - theFileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFile;
    TotalBytes += outBlock.size();
    sendOut.device()->seek(0);
    sendOut << TotalBytes << qint64((outBlock.size() - sizeof(qint64)*2));
    bytesToWrite = TotalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);
}

//实现文件的传送
void FileShareServer::updateClientProgress(qint64 numBytes)
{
    qDebug()<<tr("start to send file");
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
    if(bytesWritten == TotalBytes)//发送完毕
    {

        qDebug()<<tr("upload file successfully");
        localFile->close();
        tcpServer->close();
        localFile->close();
        bytesWritten = 0; // clear fot next send
        bytesToWrite = 0;
        TotalBytes = 0;
       //tcpSocket->close();
    }
}

void FileShareServer::on_CancelButton_clicked()
{
    if(!(ui->userTableWidget->selectedItems().isEmpty()))
    {
        int row = ui->userTableWidget->currentRow();
        if(getIP() == ui->userTableWidget->item(row,3)->text())
        {
        fileName = ui->userTableWidget->item(row, 1)->text();
        sendSignal(cancel);
        }
    }
}

void FileShareServer::on_DownLoadButton_clicked()
{
    if(!tcpServer->listen(QHostAddress::Any,tcpPort))//开始监听
    {
//        qDebug() << tcpServer->errorString();
//        close();
//        return;
    }
    this->initServer();
    sendSignal(FB);
}

void FileShareServer::initServer()
{
    payloadSize = 64*1024;
    TotalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
}

void FileShareServer::hasPendingFile(QString serverAddress,
                            QString clientAddress, QString fileName)
{
    QString ipAddress = getIP();
    qDebug()<<serverAddress<<clientAddress<<fileName;
    if(ipAddress == serverAddress)
    {
        if(!(ui->userTableWidget->selectedItems().isEmpty()))
        {
            QString name = QFileDialog::getSaveFileName(0,tr("Save File"),fileName);
            if(!name.isEmpty())
            {
                FileShareClient *client = new FileShareClient();
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
            }
        }
    }
}
