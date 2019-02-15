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

// ʹ��UDP�㲥������Ϣ
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
//            QMessageBox::warning(0,tr("����"),tr("�������ݲ���Ϊ��"),QMessageBox::Ok);
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
        qDebug()<<imageName<<tr("δ����");

        out << address  << imageName;
        qDebug()<<tr("׼������")<<imageName;

        out << QFileInfo(imageName).fileName();
        //qDebug()<<tr("��ʼд��UDP���ݱ�");
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

// ����UDP��Ϣ
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
            //��ͼ���ļ�UDP���ݰ�������ͼƬ���ļ��� temp-image/��
            createTempimageDir();
            tempFileName = QString(("temp-image/") + tempFileName);

            QImage image;
            in >> image;

            QImageWriter imageWrite(tempFileName);
            imageWrite.setFormat(QFileInfo(tempFileName).suffix().toLatin1());
            imageWrite.write(image);
            qDebug() << tr("�Ѵ����temp-image1�ļ�����");
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

// �������û�����
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
        ui->messageBrowser->append(tr("%1 ���ߣ�").arg(userName));
        ui->userNumLabel->setText(tr("����������%1").arg(ui->userTableWidget->rowCount()));

        sendMessage(WyNewParticipant);
    }
}

// �����û��뿪
void WyWidget::participantLeft(QString userName, QString localHostName, QString time)
{
    int rowNum = ui->userTableWidget->findItems(localHostName, Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->messageBrowser->append(tr("%1 �� %2 �뿪��").arg(userName).arg(time));
    ui->userNumLabel->setText(tr("����������%1").arg(ui->userTableWidget->rowCount()));
}

// ��ȡip��ַ
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

// ��ȡ�û���
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

// ���Ҫ���͵���Ϣ
QString WyWidget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();

    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
    return msg;
}


// ������Ϣ
void WyWidget::on_sendButton_clicked()
{
    if (ui->messageTextEdit->toPlainText() == "") {
        QMessageBox::warning(0,tr("����"),tr("�������ݲ���Ϊ��"),QMessageBox::Ok);
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



//����������
void WyWidget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    //��ȡ�˵�ǰѡ������壬Ȼ������Ϣ�ı���ʹ�ø�����
    ui->messageTextEdit->setCurrentFont(f);
    ui->messageTextEdit->setFocus();

}

//���������С
void WyWidget::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->messageTextEdit->setFontPointSize(arg1.toDouble());
    ui->messageTextEdit->setFocus();
}

//����Ӵ�
void WyWidget::on_boldToolBtn_clicked(bool checked)
{
    if(checked)
        ui->messageTextEdit->setFontWeight((QFont::Bold));
    else
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    ui->messageTextEdit->setFocus();
}

//������б
void WyWidget::on_italicToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

//�»���
void WyWidget::on_underlineToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}

//��ɫ����
void WyWidget::on_colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
        if (color.isValid()) {
            ui->messageTextEdit->setTextColor(color);
            ui->messageTextEdit->setFocus();
        }
}

//���������¼
void WyWidget::on_saveToolBtn_clicked()
{
    if (ui->messageBrowser->document()->isEmpty()) {
        QMessageBox::warning(0, tr("����"), tr("�����¼Ϊ�գ��޷����棡"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("���������¼"), tr("�����¼"), tr("�ı�(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }
}

//���������¼
bool WyWidget::saveFile(const QString &fileName)
{
    QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("�����ļ�"),
                                 tr("�޷������ļ� %1:\n %2").arg(fileName)
                                 .arg(file.errorString()));
            return false;
        }
        QTextStream out(&file);
        out << ui->messageBrowser->toPlainText();

        return true;
}

//��������¼
void WyWidget::on_clearToolBtn_clicked()
{
    ui->messageBrowser->clear();
}

//�رճ����ʱ�򣬷����û��뿪�Ĺ㲥���������˵���û����û��б���ɾ�����û�
void WyWidget::closeEvent(QCloseEvent *e)
{
    sendMessage(WyParticipantLeft);
    QWidget::closeEvent(e);
}

//��ȡҪ���͵��ļ���
void WyWidget::getFileName(QString name)
{
   fileName = name;
   sendMessage(WyFileName);
}


//�����ļ���ť
void WyWidget::on_sendToolBtn_clicked()
{
    if(ui->userTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("ѡ���û�"),
                       tr("���ȴ��û��б�ѡ��Ҫ���͵��û���"), QMessageBox::Ok);
        return;
    }
    server->show();
    server->initServer();
}

 //�Ƿ�����ļ�
void WyWidget::hasPendingFile(QString userName, QString serverAddress,
                            QString clientAddress, QString fileName)
{
    QString ipAddress = getIP();
    if(ipAddress == clientAddress)
    {
        int btn = QMessageBox::information(this,tr("�����ļ�"),
                                           tr("����%1(%2)���ļ���%3,�Ƿ���գ�")
                                           .arg(userName).arg(serverAddress).arg(fileName),
                                           QMessageBox::Yes,QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            QString name = QFileDialog::getSaveFileName(0,tr("�����ļ�"),fileName);
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

//������Ӱ�ť��ʵ��
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
    //ʵ��ͼ��ͬ���Ĳ���Ϊ���ȸ���ͼ���Լ��ͱ��˻����� temp-image/ �£�Ȼ�������ݰ��м���HTML����ʾ����ͼ�����
    QString image = QFileDialog::getOpenFileName(this, tr("��ͼƬ"),QDir::currentPath(), tr("Images (*.png *.bmp *.jpg)"));
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
