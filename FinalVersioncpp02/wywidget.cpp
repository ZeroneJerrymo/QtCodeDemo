#include "wyface.h"
#include "wywidget.h"
#include "ui_wywidget.h"
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QFileDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QColorDialog>
#include "wytcpserver.h"
#include "wytcpclient.h"
#include <QImageReader>
#include <QImageWriter>

WyWidget::WyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WyWidget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    port = 45454;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    server = new WyTcpServer(this);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    sendMessage(WyNewParticipant);
    connect(server, SIGNAL(sendFileName(QString)), this, SLOT(getFileName(QString)));
}

WyWidget::~WyWidget()
{
    delete ui;
}

// 使用UDP广播发送信息
void WyWidget::sendMessage(WyMessageType type, QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    out << type << getUserName() << localHostName;

    switch(type)
    {
    case WyMessage :
//        if (ui->messageTextEdit->toPlainText() == "") {
//            QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
//            return;
//        }
        out << address << getMessage();
        ui->messageBrowser->verticalScrollBar()
                ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
        break;

    case WyNewParticipant :
        out << address;
        break;

    case WyParticipantLeft :
        break;

    case WyFileName :
    {
        int row = ui->userTableWidget->currentRow();
        QString clientAddress = ui->userTableWidget->item(row, 2)->text();
        out << address << clientAddress << fileName;
        break;
     }

    case WyRefuse :
        out << serverAddress;
        break;
    case Image:
    {
        qDebug()<<imageName<<tr("未发送");

        out << address  << imageName;
        qDebug()<<tr("准备发送")<<imageName;

        out << QFileInfo(imageName).fileName();
        //qDebug()<<tr("开始写入UDP数据报");
        QImageReader imageReader(imageName);
        imageReader.setFormat(QFileInfo(imageName).suffix().toLatin1());
        out <<  imageReader.read();
        ui->messageBrowser->verticalScrollBar()
                ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
        ui->messageTextEdit->clear();

    }break;
    }

    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
}

// 接收UDP信息
void WyWidget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName,localHostName,ipAddress,message;
        QString time = QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss");

        switch(messageType)
        {
        case WyMessage:
            in >> userName >> localHostName >> ipAddress >> message;
            ui->messageBrowser->setTextColor(Qt::blue);
            ui->messageBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->messageBrowser->append("[ " +userName+" ] "+ time);
            ui->messageBrowser->append(message);
            break;

        case WyNewParticipant:
            in >>userName >>localHostName >>ipAddress;
            newParticipant(userName,localHostName,ipAddress);
            break;

        case WyParticipantLeft:
            in >>userName >>localHostName;
            participantLeft(userName,localHostName,time);
            break;

        case WyFileName:
        {
            in >> userName >> localHostName >> ipAddress;
            QString clientAddress, fileName;
            in >> clientAddress >> fileName;
            hasPendingFile(userName, ipAddress, clientAddress, fileName);
            break;
}
        case WyRefuse:
        {
            in >> userName >> localHostName;
            QString serverAddress;
            in >> serverAddress;
            QString ipAddress = getIP();

            /*if(ipAddress == serverAddress)
            {
                server->refused();
            }break;*/
        }
        case Image:
        {
            in >> userName >> localHostName >> ipAddress >> message;
            ui->messageBrowser->setTextColor(Qt::blue);
            ui->messageBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->messageBrowser->append("[ " +userName+" ] "+ time);
            QString tempFileName;
            in  >> tempFileName;
            //是图像文件UDP数据包，保存图片到文件夹 temp-image/下
            createTempimageDir();
            tempFileName = QString(("temp-image/") + tempFileName);

            QImage image;
            in >> image;

            QImageWriter imageWrite(tempFileName);
            imageWrite.setFormat(QFileInfo(tempFileName).suffix().toLatin1());
            imageWrite.write(image);
            qDebug() << tr("已存放至temp-image1文件夹内");
            QPixmap* pic = new QPixmap(tempFileName);
            int width = 100;
            int newwidth = width*(pic->size().width())/(pic->size().height());
            QString imgPath = QString("<img src=\"%1\" height=\"%2\" width=\"%3\" />").arg(tempFileName)
                    .arg(QString::number(width,10)).arg(QString::number(newwidth,10));
                    //"<img src=\":"+imgFileName+"\" />";
            ui->messageBrowser->append(imgPath);
            //continue;
        }break;


        }
    }
}

// 处理新用户加入
void WyWidget::newParticipant(QString userName, QString localHostName, QString ipAddress)
{
    bool isEmpty = ui->userTableWidget->findItems(localHostName, Qt::MatchExactly).isEmpty();
    if (isEmpty) {
        QTableWidgetItem *user = new QTableWidgetItem(userName);
        QTableWidgetItem *host = new QTableWidgetItem(localHostName);
        QTableWidgetItem *ip = new QTableWidgetItem(ipAddress);

        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0,0,user);
        ui->userTableWidget->setItem(0,1,host);
        ui->userTableWidget->setItem(0,2,ip);
        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->messageBrowser->append(tr("%1 在线！").arg(userName));
        ui->userNumLabel->setText(tr("在线人数：%1").arg(ui->userTableWidget->rowCount()));

        sendMessage(WyNewParticipant);
    }
}

// 处理用户离开
void WyWidget::participantLeft(QString userName, QString localHostName, QString time)
{
    int rowNum = ui->userTableWidget->findItems(localHostName, Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->messageBrowser->append(tr("%1 于 %2 离开！").arg(userName).arg(time));
    ui->userNumLabel->setText(tr("在线人数：%1").arg(ui->userTableWidget->rowCount()));
}

// 获取ip地址
QString WyWidget::getIP()
{
//    QList<QHostAddress> list = QNetworkInterface::allAddresses();
//    foreach (QHostAddress address, list) {
//        if(address.protocol() == QAbstractSocket::IPv4Protocol)
//            return address.toString();
//    }
//    return 0;
    QString localHostName = QHostInfo::localHostName();

    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
           return  address.toString();
    }
    return NULL;
}

// 获取用户名
QString WyWidget::getUserName()
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

// 获得要发送的消息
QString WyWidget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();

    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
    return msg;
}


// 发送消息
void WyWidget::on_sendButton_clicked()
{
    if (ui->messageTextEdit->toPlainText() == "") {
        QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok);
        return;
    }
    QString msg = ui->messageTextEdit->toHtml();
    if(msg.contains("<img src=")){
        if(msg.contains("<img src=\":/images")){
            sendMessage(WyMessage);
        }else{
            sendMessage(Image);
        }
    }else{
        sendMessage(WyMessage);
    }
}



//更改字体族
void WyWidget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    //获取了当前选择的字体，然后在消息文本中使用该字体
    ui->messageTextEdit->setCurrentFont(f);
    ui->messageTextEdit->setFocus();

}

//更改字体大小
void WyWidget::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->messageTextEdit->setFontPointSize(arg1.toDouble());
    ui->messageTextEdit->setFocus();
}

//字体加粗
void WyWidget::on_boldToolBtn_clicked(bool checked)
{
    if(checked)
        ui->messageTextEdit->setFontWeight((QFont::Bold));
    else
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    ui->messageTextEdit->setFocus();
}

//字体倾斜
void WyWidget::on_italicToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

//下划线
void WyWidget::on_underlineToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}

//颜色设置
void WyWidget::on_colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
        if (color.isValid()) {
            ui->messageTextEdit->setTextColor(color);
            ui->messageTextEdit->setFocus();
        }
}

//保存聊天记录
void WyWidget::on_saveToolBtn_clicked()
{
    if (ui->messageBrowser->document()->isEmpty()) {
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }
}

//保存聊天记录
bool WyWidget::saveFile(const QString &fileName)
{
    QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("保存文件"),
                                 tr("无法保存文件 %1:\n %2").arg(fileName)
                                 .arg(file.errorString()));
            return false;
        }
        QTextStream out(&file);
        out << ui->messageBrowser->toPlainText();

        return true;
}

//清空聊天记录
void WyWidget::on_clearToolBtn_clicked()
{
    ui->messageBrowser->clear();
}

//关闭程序的时候，发送用户离开的广播，让其他端点的用户在用户列表中删除其用户
void WyWidget::closeEvent(QCloseEvent *e)
{
    sendMessage(WyParticipantLeft);
    QWidget::closeEvent(e);
}

//获取要发送的文件名
void WyWidget::getFileName(QString name)
{
   fileName = name;
   sendMessage(WyFileName);
}


//传输文件按钮
void WyWidget::on_sendToolBtn_clicked()
{
    if(ui->userTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("选择用户"),
                       tr("请先从用户列表选择要传送的用户！"), QMessageBox::Ok);
        return;
    }
    server->show();
    server->initServer();
}

 //是否接收文件
void WyWidget::hasPendingFile(QString userName, QString serverAddress,
                            QString clientAddress, QString fileName)
{
    QString ipAddress = getIP();
    if(ipAddress == clientAddress)
    {
        int btn = QMessageBox::information(this,tr("接受文件"),
                                           tr("来自%1(%2)的文件：%3,是否接收？")
                                           .arg(userName).arg(serverAddress).arg(fileName),
                                           QMessageBox::Yes,QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),fileName);
            if(!name.isEmpty())
            {
                WyTcpClient *client = new WyTcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
        } else {
            sendMessage(WyRefuse, serverAddress);
        }
    }
}

//表情添加按钮的实现
void WyWidget::on_biaoqing_Button_clicked()
{
    QString str;
    WyFace *face = new WyFace();
    face->show();
    QString pth = "<img src=\":";
    face->exec();
    str = face->getPth();
    qDebug()<<str;
    pth += str;
    //delete face;
    pth += "\" />";
    qDebug()<<pth;
    const QString lujing = pth;
    ui->messageTextEdit->append(lujing);
}

void WyWidget::on_tupian_clicked()
{
    //实现图像同步的策略为，先复制图像到自己和别人机器的 temp-image/ 下，然后在数据包中加入HTML的显示本地图像代码
    QString image = QFileDialog::getOpenFileName(this, tr("打开图片"),QDir::currentPath(), tr("Images (*.png *.bmp *.jpg)"));
    imageName = image;
    createTempimageDir();
    QFile::copy(image, QString("temp-image/") + QFileInfo(image).fileName());
    if (image.isEmpty())
    {
        return;
    }
    QPixmap* pic = new QPixmap(image);
    int width = 100;
    int newwidth = width*(pic->size().width())/(pic->size().height());
    QString imgPath = QString("<img src=\"%1\" height=\"%2\" width=\"%3\" />").arg(image)
            .arg(QString::number(width,10)).arg(QString::number(newwidth,10));
            //"<img src=\":"+imgFileName+"\" />";
    ui->messageTextEdit->append(imgPath);
    //ui->messageTextEdit->append("<img src='temp-image/" + QFileInfo(image).fileName() + "'  />");
}

void WyWidget::createTempimageDir()
{
    QDir *temp = new QDir;
    bool exist = temp->exists("temp-image");
    if(exist)
        return;
    else
    {
       temp->mkdir("temp-image");
    }
}
