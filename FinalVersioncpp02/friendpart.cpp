#include "friendpart.h"
#include <QString>
#include <QDebug>

FriendPart::FriendPart(QWidget *parent, Qt::WindowFlags )

{
   this->parent = parent;
  //setWindowTitle(tr("ChatSimulation"));    //��Ŀ��ı���
  buttons = new QList<QToolButton*>();
  clients = NULL;
  this->layout = new QVBoxLayout(parent);
  layout->setMargin(10);   //���ò����и��������ʾ���
  layout->setAlignment(Qt::AlignHCenter);    //�����и���������ʾ��λ�ã�����Ӧ�����м�
  //layout->addStretch();    //����һ��ռλ��
  tempRect = QRect(-100, -100, -100, -100);
}


void FriendPart::insertNewClient(ClientInfo* client, QString path, bool flag) {
    if(flag == true)
    this->clients->append(client);
    QToolButton* button = new QToolButton();   //����һ��toolbutton���󹤾ߺ���
    QString objectName = client->getIpHostName();
    button->setObjectName(objectName);//ע������������ܴ������⣬.h�ļ��еķ�ʽ��������
    //        settings->setObjectName(QString::fromUtf8("settings"));
    button->setText(client->getUserName());   //�ǳ�
    button->setIcon(QPixmap(path));    //������Ƭ001
    const static QSize imageSize(HEADSIZE, HEADSIZE);
    button->setIconSize(imageSize);
   // button->setIconSize(QPixmap(path).size());
    button->setAutoRaise(true);   //�����Զ������Ƿ���ЧΪenable��
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //��ť��������ʾ���Ա�
   button->adjustSize();
    if(tempRect.width() != (-100)) {
        button->setGeometry(QRect(tempRect.x(), tempRect.y() + tempRect.height(),
                                  tempRect.width(), tempRect.height()));
    }
    this->tempRect = button->geometry();
    //qDebug() << this->tempRect.x() << this->tempRect.y() << this->tempRect.width() <<this->tempRect.height();
    this->buttons->append(button);
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(clickFriend()));
    //QObject::connect(button, SIGNAL())
}

void FriendPart::clickFriend() {

    QListIterator<ClientInfo*> iter(*clients);
    while(iter.hasNext()) {
        ClientInfo* client = iter.next();
        if((sender()->objectName() == (client->getIpHostName())) && (*(client->getFlagPosition()) == false)) {
            client->setWindow(client->getIpAddress(), client->getIpHostName(),
                       client->getUserName(), client->getImageHead2(), client->getFlagPosition());
           // qDebug() << "client ip" << client->getIpAddress() << "HostName:" << client->getIpHostName();
            client->getWindow()->show();
        }
    }
}

FriendPart::~FriendPart() {
    delete buttons;
}

void FriendPart::setClientInfo(QList<ClientInfo *> *clients) {
    this->clients = clients;
}


void FriendPart::addMoreWidgets() {
    /*
    QListIterator<QToolButton*> iter(*buttons);
    while(iter.hasNext()) {
        QToolButton* button = iter.next();
        layout->addWidget(button);
    }
    */
    layout->addWidget(buttons->last());
}

void FriendPart:: deleteButton(QString hostName) {

    QListIterator<QToolButton*> iter(*buttons);
    int index = 0;
    while(iter.hasNext()) {
        QToolButton* client = iter.next();
        if(client->objectName() == hostName) {
            delete client;
            buttons->removeAt(index);
        }
        index++;
    }
}
/*
void FriendPart::mousePressEvent(QMouseEvent *event) {
    qDebug() << "haha";
    if (event->button() == Qt::LeftButton) {
        qDebug() << "right button release";
        qDebug() << "x:" << QString::number(event->x()) <<
                    "y:" << QString::number(event->y());
    }
}
*/
