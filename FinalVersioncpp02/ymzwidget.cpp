#include "ymzwidget.h"
#include "ui_ymzwidget.h"
#include "face.h"


#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include <QFileDialog>

#include <QColorDialog>
#include <QString>
#include <QDebug>
#include <QSettings>


/*Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    port = 45457;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}*/

Widget::Widget(QString ip, QString hostName, QString userName, QString imagePath,  bool* flag,QWidget *parent):
    QWidget(parent),
    ui(new Ui::Widget)
{
    qDebug()<<"setWindow ok";
    ui->setupUi(this);
    this->flag = flag;
    *(this->flag) = true;
    udpSocket = new QUdpSocket(this);
    port = 45457;
    server = new TcpServer(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    ui->toolButton->setIcon(QIcon(imagePath));
    ui->lineEdit->setText(userName);
    ui->lineEdit_2->setText(hostName);
    ui->lineEdit_3->setText(ip);
    this->setWindowTitle(tr("��") + userName +tr("������"));
    qDebug()<<"set information ok";
    connect(server, SIGNAL(sendFileName(QString)), this, SLOT(getFileName(QString)));
    //qDebug()<<userName + "success";
    //connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage(MessageType type)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    QSettings settings("info.ini", QSettings::IniFormat);

    QString imageHead2= settings.value("infomation/User_icon").toString();

    out << type << getUserName() << localHostName;
    QHostAddress adr = QHostAddress(ui->lineEdit_3->text());

    switch(type)
    {
    case Message:
    {
        QString msg = getMessage();

         out << address << imageHead2 << msg;//��ip��ַ�͵õ�����Ϣ��������out������
         ui->textBrowser->verticalScrollBar()    //���ش�ֱ��
                       ->setValue(ui->textBrowser->verticalScrollBar()->maximum());//���ô�ֱ�����������ֵ

        //qDebug()<<address + "success";

        QString time = QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss");
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->setCurrentFont(QFont("Times New Roman",12));
        ui->textBrowser->append("[ " +getUserName()+" ] "+ time);
        //qDebug() << ui->textEdit->toPlainText();
        ui->textBrowser->append(msg);
        //qDebug()<<time;
        //udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
        break;
    }
    case FileName:
    {
        out << address << fileName;
        break;
    }

    }

    udpSocket->writeDatagram(data, data.length(), adr, 45455);
}

/*void Widget::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize((udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);

        QString userName, localHostName, ipAddress, message;
        QString time = QDateTime::currentDateTime()
                .toString("yyyy-MM-dd hh:mm:ss");

            in >> userName >> localHostName >> ipAddress >> message;
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->textBrowser->append("[ " +userName+" ] "+ time);
            ui->textBrowser->append(message);
            qDebug()<<ui->textBrowser->toPlainText();
            qDebug()<<time;
     }
}*/

QString Widget::getIP()
{
    QString localHostName = QHostInfo::localHostName();

    QHostInfo info = QHostInfo::fromName(localHostName);
    foreach(QHostAddress address, info.addresses())
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
           return  address.toString();
    }
    return NULL;
}

QString Widget::getUserName()
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
                return stringList.at(1);//at(0)Ϊ����"USERNAME."��at(1)Ϊ�û���
                break;
            }
        }
    }
    return "unknown";
}

QString Widget::getMessage()
{
    QString msg = ui->textEdit->toHtml();//ת����html���Խ��з���

    ui->textEdit->clear();//���������������
    ui->textEdit->setFocus();//�������ù�����뽹�㣬�����㱣�ֲ���
    return msg;
}

void Widget::on_pushButton_clicked()
{
    sendMessage(Message);
}

// ����������
void Widget::on_fontComboBox_currentFontChanged(QFont f)
{
    ui->textEdit->setCurrentFont(f);
    ui->textEdit->setFocus();
}


// ���������С
void Widget::on_sizeComboBox_currentIndexChanged(QString size)
{
    ui->textEdit->setFontPointSize(size.toDouble());
    ui->textEdit->setFocus();
}

// �Ӵ�
void Widget::on_toolButton_2_clicked(bool checked)
{
    if(checked)
        {
        ui->textEdit->setFontWeight(QFont::Bold);
        //qDebug()<<"jiachu";
        }
    else
        ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setFocus();
}

// ��б
void Widget::on_italicToolBtn_clicked(bool checked)
{
    ui->textEdit->setFontItalic(checked);
    ui->textEdit->setFocus();
}

// �»���
void Widget::on_underlineToolBtn_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
    ui->textEdit->setFocus();
}

// ��ɫ
void Widget::on_colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid()) {
        ui->textEdit->setTextColor(color);
        ui->textEdit->setFocus();
    }
}

void Widget::currentFormatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());

    // ��������С����(��Ϊ������С������Ϊ9)��ʹ��12
    if (format.fontPointSize() < 9) {
        ui->sizeComboBox->setCurrentIndex(3);
    } else {
        ui->sizeComboBox->setCurrentIndex( ui->sizeComboBox
                                          ->findText(QString::number(format.fontPointSize())));
    }
    ui->toolButton_2->setChecked(format.font().bold());
    ui->italicToolBtn->setChecked(format.font().italic());
    ui->underlineToolBtn->setChecked(format.font().underline());
    color = format.foreground().color();
}

void Widget::closeEvent(QCloseEvent *) {
   *(this->flag) = false;
   // this->close();
    delete this;
    //qDebug()<<"delete ui";
   // e->accept();
   // e->a
}

void Widget::setText(QString msg) {
    QString time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");
    ui->textBrowser->setTextColor(Qt::blue);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",12));
    ui->textBrowser->append("[ " +ui->lineEdit->text()+" ] "+ time);
    ui->textBrowser->append(msg);
    //qDebug()<<"���" +msg + "���";
}
void Widget::on_face_clicked()
{
    QString str;
    FFace *face = new FFace();
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
    ui->textEdit->append(lujing);
    //const QString cs = "<img src=\":/resource/images/face/03.png\" />";
    //ui->textEdit->append(cs);
    //ui->textEdit->setText("<img src=\":/resource/images/face/04.png\" />");
}
// ���������¼
void Widget::on_saveToolBtn_clicked()
{
    if (ui->textBrowser->document()->isEmpty()) {
        QMessageBox::warning(0, tr("����"), tr("�����¼Ϊ�գ��޷����棡"), QMessageBox::Ok);
    } else {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("���������¼"), ui->lineEdit->text()+tr("�����¼"), tr("�ı�(*.txt);;All File(*.*)"));
        if(!fileName.isEmpty())
            saveFile(fileName);
    }
}

// ���������¼
bool Widget::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("�����ļ�"),
                             tr("�޷������ļ� %1:\n %2").arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->textBrowser->toPlainText();

    return true;
}

void Widget::on_file_clicked()
{
    //server = new TcpServer();
    server->show();
    server->initServer();
}
//��ȡҪ���͵��ļ���
void Widget::getFileName(QString name)
{
    qDebug()<<"getFileName";
   fileName = name;
   sendMessage(FileName);
}

void Widget::on_clear_clicked()
{
    ui->textBrowser->clear();
}
