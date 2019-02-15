#ifndef COS_GROUPCHAT_H
#define COS_GROUPCHAT_H

#include <QWidget>
#include <QWebEngineView>
#include <QTextEdit>
#include "ui_cos_groupchat.h"
#include "cos_tcpconnectmanger.h"
#include "document.h"
class Cos_TcpConnectManger;
class Cos_GroupChat : public QWidget
{
    Q_OBJECT

public:
    Cos_GroupChat(QWidget *parent = Q_NULLPTR);
    ~Cos_GroupChat();

private:
    Ui::Cos_GroupChat ui;
public slots:
    void ppppp();
    void ppppp1();
    void slot_btnpicClicked();
    void slot_lineEditReturnpressed();
private:
    QWebEngineView *m_pView;
    QTextEdit* pTextEdit1;
    QTextEdit* pTextEdit2;
    QString otherhead;
    QString Myhead;
    Cos_TcpConnectManger* pManager;
    Document m_content;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
 signals:
    void sendMessage(QString);
protected:
    void SendMsgShow(QString msg, QString head);
    void RevMsgShow(QString msg, QString head);
    QString getHeadId(QString labelID);
    QString getTextId(QString labelID);
protected slots:
    void updateMessage();
    void clearLastMessage();
private slots:
    void slot_receiveMessage(QString);
    void slot_deleteMessage(QString);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    int  sendDivID;
    int  RecvDIvID;
    QMap<QString, QString> mp_idToMsg;

};

#endif // COS_GROUPCHAT_H
