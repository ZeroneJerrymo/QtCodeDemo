#include "friendpart.h"
#include <QString>
#include <QDebug>

FriendPart::FriendPart(QWidget *parent, Qt::WindowFlags )

{
   this->parent = parent;
  //setWindowTitle(tr("ChatSimulation"));    //项目框的标题
  buttons = new QList<QToolButton*>();
  clients = NULL;
  this->layout = new QVBoxLayout(parent);
  layout->setMargin(10);   //设置布局中各窗体的显示间距
  layout->setAlignment(Qt::AlignHCenter);    //布局中各个窗体显示的位置，这里应该是中间
  //layout->addStretch();    //插入一个占位符
  tempRect = QRect(-100, -100, -100, -100);
}


void FriendPart::insertNewClient(ClientInfo* client, QString path, bool flag) {
    if(flag == true)
    this->clients->append(client);
    QToolButton* button = new QToolButton();   //创建一个toolbutton对象工具盒类
    QString objectName = client->getIpHostName();
    button->setObjectName(objectName);//注意了这里可以能存在问题，.h文件中的方式是这样的
    //        settings->setObjectName(QString::fromUtf8("settings"));
    button->setText(client->getUserName());   //昵称
    button->setIcon(QPixmap(path));    //引入照片001
    const static QSize imageSize(HEADSIZE, HEADSIZE);
    button->setIconSize(imageSize);
   // button->setIconSize(QPixmap(path).size());
    button->setAutoRaise(true);   //设置自动浮起是否有效为enable。
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //按钮的文字显示在旁边
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
