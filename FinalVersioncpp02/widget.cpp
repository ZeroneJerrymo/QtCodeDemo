#include "widget.h"
#include "clientinfo.h"
#include <QUdpSocket>
#include <QHostInfo>
#include <QProcess>
#include <QHostAddress>
#include <QNetworkInterface>
#include "readxml.h"
#include "QMessageBox"
#include "writexml.h"
#include <QFileDialog>
#include "set.h"
#include<QString>
#include<QSettings>
#include<QIcon>
#include "wywidget.h"
#include"help.h"
#include"sysbutton.h"
//#include <QTextCodec>

widget::widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FeiQ)
{
    ui->setupUi(this);
     this->setWindowFlags(Qt::FramelessWindowHint);
    btnMin=new sysButton("sys_button_min.png",tr("最小化"));
    connect(btnMin,SIGNAL(clicked()),this,SLOT(showMin()));
    btnClose=new sysButton("sys_button_close.png",tr("关闭"));
    connect(btnClose,SIGNAL(clicked()),this,SLOT(showclose()));//关闭 记者要发送离开信息

    ui->MainwindowLayout->addStretch();
    ui->MainwindowLayout->addWidget(btnMin);
    ui->MainwindowLayout->addWidget(btnClose);
    ui->MainwindowLayout->setSpacing(0);
    ui->MainwindowLayout->setContentsMargins(0,0,0,0);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("gbk"));
    this->diffParts = new QList<FriendPart*>();
    this->clients = new QList<ClientInfo*>();
    this->buttons = new QList<GroupInfo*>();
    this->widgets = new QList<QWidget*>();
    this->rightButton = NULL;
    ui->toolButtonPixmap->setIcon(QIcon(Head_icon));
    init();
    generateButtonGroups();

    udpSocket = new QUdpSocket(this);
    port = 45455;
    this->setWindowTitle("FeiQ");
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    connect(ui->toolButton_3,SIGNAL(clicked()),this,SLOT(to_setting()));
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(to_resh()));
    this->broadMessage();
    tixing();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
}

widget::~widget()
{
    delete ui;
    delete clients;
}

Ui::FeiQ * widget:: getUI() {
    return this->ui;
}

void widget::to_resh(){
   QSettings  settings("info.ini", QSettings::IniFormat);
//    int mainFun = settings.value("DevOption/mainFun").toInt();
    QString name_ini = settings.value("infomation/User_name").toString();
    QString sign_ini = settings.value("infomation/User_sign").toString();
    Head_icon = settings.value("infomation/User_icon").toString();
    ui->labelPetName->setText(name_ini);
    ui->lineEditSignature->setText(sign_ini);
    ui->toolButtonPixmap->setIcon(QIcon(Head_icon));
    ui->toolButtonPixmap->setIconSize(QSize(80,80));//ͷ���Ĵ�С�ͳ�ʼ��

    this->broadMessage();
}

void widget::to_setting(){

    n = new set();
    n->show();
}
void widget::processPendingDatagrams()
{

    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize((udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;

        QString userName, localHostName, ipAddress;



        switch(messageType)
        {
        case Message: {
            QString msg;
            QString imageHead2;
            in >> userName >> localHostName >> ipAddress >> imageHead2 >> msg;
            QListIterator<ClientInfo*> iter(*clients);
            while(iter.hasNext()) {
                ClientInfo* client = iter.next();
                if((client->getIpAddress() == ipAddress)) {
                    if(*(client->getFlagPosition()) == false) {
                        client->setWindow(client->getIpAddress(), client->getIpHostName(),
                                   client->getUserName(), imageHead2, client->getFlagPosition());
                        client->getWindow()->show();
                    }
                    client->getWindow()->setText(msg);
                }
            }
                        break;
        }

        case NewParticipant:
        {
            QString imageHead , imageHead2;
            in >>userName >>localHostName >>ipAddress >> imageHead >> imageHead2;
            qDebug() << "imageHead" << imageHead;
            qDebug() << "imageHead2" << imageHead2;
            //imageId = 15;
            if(ipAddress != "")
            newParticipant(userName,localHostName,ipAddress, imageHead, imageHead2);
            break;
        }

        case ParticipantLeft:
        {
             in >>userName >>localHostName >>ipAddress;
             deleteParticipant(localHostName, ipAddress);
            break;
        }

        case FileName:
        {
            qDebug()<<"sucess";
            in >> userName >> localHostName >> ipAddress;
            QString fileName;
            in >>fileName;
            hasPendingFile(userName, ipAddress, fileName);
            break;
        }
        case Refuse:
        {
            in >> userName >> localHostName;
            QString serverAddress;
            in >> serverAddress;
            QString ipAddress = getIP();

            //server->refused();
            QListIterator<ClientInfo*> iter(*clients);
            while(iter.hasNext()) {
                ClientInfo* client = iter.next();
                if((client->getIpAddress() == ipAddress))
                    client->getWindow()->server->refused();
            }
        }
        }
    }
}


void widget::broadMessage() {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    QSettings settings("info.ini", QSettings::IniFormat);
    QString imageHead = settings.value("infomation/User_photo").toString();
    //QSettings settings("info.ini", QSettings::IniFormat);
    QString imageHead2 = settings.value("infomation/User_icon").toString();

    out << NewParticipant << getUserName() << localHostName;
    out << address << imageHead << imageHead2;

    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast, port);
}

QString widget::getUserName() {
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


// ��ȡip��ַ
QString widget::getIP()
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


void widget::newParticipant(QString userName,
                    QString localHostName, QString ipAddress, QString imageHead, QString imageHead2) {
    QListIterator<ClientInfo*> iter(*clients);
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();

        if(client->getIpAddress() == ipAddress) {
            client->setImageHead(imageHead);
            client->setImageHead2(imageHead2);
            QString hostName = "";
            hostName = client->getIpHostName();
            qDebug() << "229";
            int i = 0;
            int j = 0;
            bool flag2 = false;

            QListIterator<GroupInfo*> iter2(*(this->buttons));
            while(iter2.hasNext()  && (!flag2)) {
                GroupInfo* group = iter2.next();
                QListIterator<ClientCode*> iter3(*(group->getClients()));
                while(iter3.hasNext()) {
                    ClientCode* clientCode = iter3.next();
                    if(clientCode->getComputerCode() == ipAddress) {
                        flag2 = true;
                        break;
                    }
                    i++;
                }
                if(flag2 == true) break;
                j++;
                i = 0;
            }

            if(j >= (this->buttons->length())) {
                this->diffParts->at(0)->deleteButton(hostName);
                j = 0;
            }
            else {
                this->diffParts->at(j)->deleteButton(hostName);
            }
                QString path = client->getImageHead();
                this->diffParts->at(j)->insertNewClient(client, path, false);
                this->diffParts->at(j)->addMoreWidgets();
            return;
        }
    }

   ClientInfo* client = new ClientInfo(userName, localHostName, ipAddress, imageHead, imageHead2);
   FriendPart* drawer = judgeGroup(ipAddress);
    drawer->insertNewClient(client, imageHead);
    drawer->addMoreWidgets();
    if(ipAddress != getIP()) {
        sendMessage(NewParticipant, ipAddress);
    }
}


void widget::sendMessage(MessageType type, QString serverAddress) {

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    QSettings settings("info.ini", QSettings::IniFormat);
    QString imageHead = settings.value("infomation/User_photo").toString();
    QString imageHead2 = settings.value("infomation/User_icon").toString();
    out << type << getUserName() << localHostName<<address << imageHead << imageHead2;

    switch(type)
    {
    case NewParticipant : {
        QHostAddress adr = QHostAddress(serverAddress);
        udpSocket->writeDatagram(data,data.length(), adr,  this->port);
        break;
    }
    case ParticipantLeft :
        udpSocket->writeDatagram(data,data.length(), QHostAddress::Broadcast,  this->port);
        break;
    case Refuse :
        QHostAddress adr = QHostAddress(serverAddress);
        udpSocket->writeDatagram(data,data.length(), adr,  this->port);
        break;
    }
}


void widget::closeEvent(QCloseEvent *e ) {
    sendMessage(ParticipantLeft);
    QWidget::closeEvent(e);
     WriteXML write;
     write.writeInformation(this->buttons);
}


void widget:: deleteParticipant(QString hostName, QString ipAddress) {

    QListIterator<ClientInfo*> iter(*clients);
    int i = 0;
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();
        if((client->getIpAddress() == ipAddress)) {
            if(*(client->getFlagPosition()) == true) {
                delete client->getWindow();
                *(client->getFlagPosition()) = false;
            }
            delete client;
            clients->removeAt(i);
            FriendPart* part = judgeGroup(ipAddress);
            part->deleteButton(hostName);
        }
        i++;
    }
}




void widget::init() {
    qDebug() << "342";
    const QString path = "person.xml";
    qDebug() << "343";
    ReadXML read(path);
    read.getInformation(&(this->buttons));
    QSettings  settings("info.ini", QSettings::IniFormat);
     QString name_ini = settings.value("infomation/User_name").toString();
     QString sign_ini = settings.value("infomation/User_sign").toString();
     Head_icon = settings.value("infomation/User_icon").toString();
     ui->labelPetName->setText(name_ini);
     ui->lineEditSignature->setText(sign_ini);
     ui->toolButtonPixmap->setIcon(QIcon(Head_icon));
     ui->toolButtonPixmap->setIconSize(QSize(80,80));//ͷ
}


void widget::generateButtonGroups() {

    ToolBox = new QToolBox(this->ui->tab);
    ToolBox->setObjectName(QString::fromUtf8("ToolBox"));
    ToolBox->setGeometry(QRect(0, 0, 291, 271));

    qDebug() << this->buttons->length();
    for(int i = 0; i < this->buttons->length(); i++) {
        //this->buttonGroups->append(new QList<QToolButton*>());
        QString groupName = this->buttons->at(i)->getGroupName();
        QWidget* newWidget = new QWidget();
        newWidget->setObjectName(groupName);
        newWidget->setGeometry(QRect(0, 0, 291, 193));
        this->widgets->append(newWidget);
        this->ToolBox->addItem(newWidget, groupName);
        this->diffParts->append(new FriendPart(newWidget));
        this->diffParts->last()->setClientInfo(this->clients);
    }
}


FriendPart* widget::judgeGroup(QString ipAddress) {

    QListIterator<GroupInfo*> iter(*buttons);
    int loop = 0;
    while(iter.hasNext()) {
         GroupInfo* group = iter.next();
          QListIterator<ClientCode*> iter2(*(group->getClients()));
          while(iter2.hasNext()) {
              ClientCode* client = iter2.next();
              if(client->getComputerCode() == ipAddress) {
                 return  this->diffParts->at(loop);
              }
         }
          loop++;
      }
    return  NULL ;
}

void widget::mouseReleaseEvent(QMouseEvent* event) {
    if(event->button() == Qt::RightButton) {
        if((event->x() >= 12) && (event->x() <= 300) &&
                (event->y() <= 509) && (event->y() >= 242)) {
            this->rightButton = new ClickRightButton(this);
            this->rightButton->show();
           // delete this->rightButton;
        }
    }
}

void widget::rightButtonClickNewGroup() {
   // qDebug() << "rightButtonClick length:" << this->buttonGroups->length();
   // this->buttonGroups->append(new QList<QToolButton*>());
    QString groupName = this->rightButton->getNewGroup()->text();
    qDebug() << groupName;
    this->buttons->append(new GroupInfo(groupName));

    QWidget* newWidget = new QWidget();
    newWidget->setObjectName(groupName);
    newWidget->setGeometry(QRect(0, 0, 291, 193));
    this->widgets->append(newWidget);
    this->ToolBox->addItem(newWidget, groupName);
    this->diffParts->append(new FriendPart(newWidget));
    this->diffParts->last()->setClientInfo(this->clients);

    //qDebug() << "ɾ���˷���";
}


void widget::rightButtonDeleteGroup() {

    QString groupName = this->rightButton->getNewGroup()->text();
    qDebug() << groupName;
    bool flag = false;
    int i = 0;
    qDebug() << "rightButtonDeleteGroup length:" << this->buttons->length();
    for(; i < (this->buttons->length()); i++) {
        if((this->buttons->at(i)->getGroupName()) == groupName) {
            if(i == 0) {
                QMessageBox::warning(this,tr("NOT ALLOW"),QString("Not allow to delete default group!"),QMessageBox::Yes);
                return ;
            }
             QList<ClientCode*>*  deleteClients= this->buttons->at(i)->getClients();
             moveToDefaultGroup(deleteClients);
             //qDebug() << "this->buttonsName:" << this->buttons->at(i)->getGroupName();
             //qDebug() << "groupName" << groupName;
             //qDebug() << "deleteClients length" << deleteClients->length();

            this->buttons->removeAt(i);
             qDebug() << "Test01";
             flag = true;
             break;
        }
    }
    qDebug() << "i index:" << i;
    if(flag != true) {
        QMessageBox::warning(this,tr("NOT EXIST"),QString("Group is not exist!"),QMessageBox::Yes);
        return ;
    }
    //QList<QToolButton*>* deleteButtons = this->buttonGroups->at(i);
    //qDebug() << "buttonGroups length" << this->buttonGroups->length();
  //  qDebug() << "deleteButtons length" << deleteButtons->length();
   // for(int j = 0; j < deleteButtons->length(); j++) {
  //      delete deleteButtons->at(j);
 //       deleteButtons->removeAt(j);
 //   }
    this->ToolBox->removeItem(i);
    //this->buttonGroups->removeAt(i);

    delete this->widgets->at(i);
    this->widgets->removeAt(i);
    delete this->diffParts->at(i);
    this->diffParts->removeAt(i);

}

void widget::moveToDefaultGroup(QList<ClientCode*>* moveClients) {

    QListIterator<ClientCode*> iter(*moveClients);
    while(iter.hasNext()) {
        ClientCode* clientCode = iter.next();
        QListIterator<ClientInfo*> iter2(*(this->clients));
        while(iter2.hasNext()) {
            ClientInfo* clientInfo = iter2.next();
            if(clientInfo->getIpAddress() == clientCode->getComputerCode()) {
                //�������ӵ���һ����ȥ��
                QString path = clientInfo->getImageHead();
                this->diffParts->at(0)->insertNewClient(clientInfo, path, false);
                this->diffParts->at(0)->addMoreWidgets();
                break;
            }
        }
    }
}

void widget::moveButtonToNewGroup() {
    QString userName = this->rightButton->getMoveUi()->getUserName();
    QString groupName = this->rightButton->getMoveUi()->getGroupName();

    if(!judgeLegel(userName, groupName)) {
        QMessageBox::warning(this,tr("����"),QString("userName or groupName illegal"),QMessageBox::Yes);
        return ;
    }
    QString ip = "";
    QString hostName = "";
    QListIterator<ClientInfo*> iter(*(this->clients));
    ClientInfo* userInfo = NULL;
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();
        if(client->getUserName() == userName) {
            ip = client->getIpAddress();
            hostName = client->getIpHostName();
            userInfo = client;
            break;
        }
    }
    if(ip == "") return;
    int i = 0;
    int j = 0;
    bool flag2 = false;
    QListIterator<GroupInfo*> iter2(*(this->buttons));
    while(iter2.hasNext()  && (!flag2)) {
        GroupInfo* group = iter2.next();
        QListIterator<ClientCode*> iter3(*(group->getClients()));
        while(iter3.hasNext()) {
            ClientCode* clientCode = iter3.next();
            qDebug() << clientCode->getComputerCode();
            if(clientCode->getComputerCode() == ip) {
                group->getClients()->removeAt(i);
                flag2 = true;
                break;
            }
            i++;
        }
        if(flag2 == true) break;
        j++;
        i = 0;
    }

    if(flag2 != false) {
        this->diffParts->at(j)->deleteButton(hostName);
    }
    else {
        this->diffParts->at(0)->deleteButton(hostName);
    }

    int p = 0;
    QListIterator<GroupInfo*> iter4(*(this->buttons));
    while(iter4.hasNext()) {
        GroupInfo* group = iter4.next();
        if(group->getGroupName() == groupName) {
            ClientCode* tempClient = new ClientCode();
            tempClient->setComputerCode(ip);
            group->getClients()->append(tempClient);
            break;
        }
        p++;
    }

    if(userInfo != NULL) {
        QString path = userInfo->getImageHead();
        this->diffParts->at(p)->insertNewClient(userInfo, path, false);
        this->diffParts->at(p)->addMoreWidgets();
    }
}





bool widget::judgeLegel(QString userName , QString groupName) {
    bool flag = false;
    QListIterator<ClientInfo*> iter(*this->clients);
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();
        if(client->getUserName() == userName) {
            flag = true;
            break;
        }
    }

    if(flag == false) return false;
    //�ж������Ƿ��Ϸ�

    QListIterator<GroupInfo*> iter2(*(this->buttons));
    while(iter2.hasNext()) {
        GroupInfo* group = iter2.next();
        if(group->getGroupName() == groupName) {
            return true;
        }
    }

    return false;
}
//�Ƿ������ļ�
void widget::hasPendingFile(QString userName, QString serverAddress,
                            QString fileName)
{

        int btn = QMessageBox::information(this,tr("�����ļ�"),
                                           tr("���%1(%2)���ļ���%3,�Ƿ����գ�")
                                           .arg(userName).arg(serverAddress).arg(fileName),
                                           QMessageBox::Yes,QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            QString name = QFileDialog::getSaveFileName(0,tr("�����ļ�"),fileName);
            if(!name.isEmpty())
            {
                TcpClient *client = new TcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
        } else {
            sendMessage(Refuse, serverAddress);
        }
}

void widget::on_pushButton_clicked()
{
    w = new WyWidget();
    w->show();
}

//打开应用中心
void widget::on_toolButton_4_clicked()
{
    add *yingyong=new add;
    yingyong->show();
}
//备忘录事件发生日期提醒
void widget::tixing(){
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd"); //设置显示格式
    QString filename="date/"+str+".txt";
    QFile file(filename);

    //QFile *file1=new QFile( filename );  //file.setFileName( "xx.txt" );
    if ( file.exists())
    {
        QTextCodec *code=QTextCodec::codecForName("UTF-8");//本人采用的是UTF8格式显示的
        //QFile file("/file.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        stream.setCodec(code);//输出流的设置--------必须嘀

          QMessageBox msg;
          msg.setWindowTitle("Infomation");
         // char *ch=line;
          msg.setText(stream.readLine());
          //msg.showEvent();
          //msg.setFixedSize(200,70);
          //msg.setStyleSheet("font: 14pt;background-color:rgb( 0,220, 0)");
          msg.setIcon(QMessageBox::Information);
          msg.addButton("I know!",QMessageBox::ActionRole);
          msg.exec();
          //file1->close();
          return;
    }
}



//打开帮助
void widget::on_helpbutton_clicked()
{
    h = new help();
    h->show();
}

void widget::on_FileShare_clicked()
{
    F = new FileShareServer();
    F->show();
}

void widget::on_pushButtonClose_clicked()
{
    QApplication::exit();
}

void widget::on_pushButtonMin_clicked()
{
    setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
}

void widget::showMin()
{
    showMinimized();
}

void widget::showclose()
{
    this->close();
}
void widget::mousePressEvent(QMouseEvent *e)
{

     this->windowPos = this->pos();
     this->mousePos = e->globalPos();
     this->dPos = mousePos - windowPos;
}

void widget::mouseMoveEvent(QMouseEvent *e)
{

     this->move(e->globalPos() - this->dPos);
}
void widget::mouseReleaseEvent1(QMouseEvent *e)
{
    if(isMove)
        isMove=false;
}
void widget::on_lineEditSearch_returnPressed()
{
    QString name = this->ui->lineEditSearch->text();
    int number = findUserNameInWhichGroup(name);
    if(number != -1) {
        QWidget* currentWidget = this->widgets->at(number);
        this->ToolBox->setCurrentWidget(currentWidget);
    }
}


int widget::findUserNameInWhichGroup(QString userName) {
    //查找用户所在的组的下标，如果不存在的话返回-1,
    QString ip = "";
    QString hostName = "";
    QListIterator<ClientInfo*> iter(*(this->clients));
    ClientInfo* userInfo = NULL;
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();
        if(client->getUserName() == userName) {
            ip = client->getIpAddress();
            hostName = client->getIpHostName();
            userInfo = client;
            break;
        }
    }
    if(ip == "") return -1;

    int j = 0;
    bool flag2 = false;
    QListIterator<GroupInfo*> iter2(*(this->buttons));
    while(iter2.hasNext()  && (!flag2)) {
        GroupInfo* group = iter2.next();
        QListIterator<ClientCode*> iter3(*(group->getClients()));
        while(iter3.hasNext()) {
            ClientCode* clientCode = iter3.next();
            if(clientCode->getComputerCode() == ip) {
                flag2 = true;
                break;
            }
        }
        if(flag2 == true) break;
        j++;
    }

    return j;
}

