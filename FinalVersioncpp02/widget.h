#ifndef WIDGET_H
#define WIDGET_H

#include"sysbutton.h"
#include <QDialog>
#include "clientinfo.h"
#include <QList>
#include "ui_lilintao.h"
#include "ui_widget.h"
#include "friendpart.h"
#include "ymzwidget.h"
#include "groupinfo.h"
#include "clickrightbutton.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "set.h"
#include "wywidget.h"
#include "yingyong.h"
#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <help.h>
#include "fileshareserver.h"
#include <QToolBox>
class QUdpSocket;

namespace Ui {
class widget;
}

class ClickRightButton;

class widget : public QDialog
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    QString Head_icon;
    sysButton *btnMin;
    //sysButton *btnMax;
    sysButton *btnClose;
    ~widget();

private:
   //Ui::widget *ui;
    Ui::FeiQ *ui;
    QList<ClientInfo* > *clients;
    QUdpSocket *udpSocket;
    qint16 port;
   // QList<QList<QToolButton*>*>* buttonGroups;
    QList<GroupInfo*>* buttons;
    QList<QWidget*>* widgets;
    QList<FriendPart*>* diffParts;
    QToolBox* ToolBox;
    help * h;

    void init();
    void generateButtonGroups();
    ClickRightButton* rightButton;

     set *n;
     WyWidget *w;
     FileShareServer *F;
private slots:
    void processPendingDatagrams();

    void to_resh();
    void to_setting();

    void on_pushButton_clicked();

    void on_toolButton_4_clicked();

    void on_helpbutton_clicked();

    void on_FileShare_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonMin_clicked();

    void showMin();

    void showclose();

    void on_lineEditSearch_returnPressed();

public:
   //QList<QList<QToolButton*>*>* getButtonGroups();
    Ui::FeiQ * getUI();
    void broadMessage();
    void hasPendingFile(QString userName, QString serverAddress,
                        QString fileName);//�ж��Ƿ������ļ�
public slots:
    void rightButtonClickNewGroup();
    void rightButtonDeleteGroup();
    void moveButtonToNewGroup();

private:
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    bool isMove;
    QString getUserName();
    QString getIP();
    //void returnPersonMessage(QString ipAddress);

    void newParticipant(QString userName,
                            QString localHostName, QString ipAddress, QString imageHead, QString imageHead2);
    void sendMessage(MessageType type, QString serverAddress="");
    void deleteParticipant(QString hostName, QString ipAddress);
    void closeEvent(QCloseEvent *);
    FriendPart* judgeGroup(QString ipAddress);
    void moveToDefaultGroup(QList<ClientCode*>* );
    bool judgeLegel(QString userName , QString groupName);
    int findUserNameInWhichGroup(QString userName);
    void tixing();
protected:

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseReleaseEvent1(QMouseEvent *);
};

#endif // WIDGET_H
