#include "cos_groupchat.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QWebEnginePage>
//#include <QWebChannel>
#include <QPushButton>
#include <QSplitter>
#include <QApplication>
#include <QWebEngineSettings>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QWheelEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QWebChannel>
Cos_GroupChat::Cos_GroupChat(QWidget *parent)
    : QWidget(parent), sendDivID(0), RecvDIvID(0)
{
    ui.setupUi(this);
    this->setMinimumWidth(250);

    this->setWindowTitle("DDLT");
    //this->setWindowIcon
    //设置我方头像和对方头像
    Myhead = "<img src=qrc:/resource/myHead.png width='30px'heigth='30px'>";
    QString strHead = QString("qrc:/resource/otherHead.png");
    otherhead = QString("<img src=%1 width='30px' heigth='30px'>").arg(strHead);

    m_pView = new QWebEngineView(this);
    m_pView->installEventFilter(this);
    ui.m_textEdit_send->installEventFilter(this);
    //m_pView->setContextMenuPolicy(Qt::NoContextMenu); //禁用右击
    //m_pView->setStyleSheet("background-color:#ffffff");
    QWebEnginePage *pPage = new QWebEnginePage(this);
    m_pView->setPage(pPage);
    Document*  m_content = new Document(this);
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("contentObj"), m_content);
    pPage->setWebChannel(channel);

    //加载HTML模板
    m_pView->page()->load(QUrl("qrc:/resource/messageBox.html"));
    QVBoxLayout *pMai = new QVBoxLayout;
    pMai->addWidget(m_pView);
    pMai->setContentsMargins(0, 0, 0, 0);
    ui.m_pframe->setLayout(pMai);

   pManager = new Cos_TcpConnectManger;



    connect(ui.m_Btn_Send, SIGNAL(clicked()), this, SLOT(slot_lineEditReturnpressed()));
    connect(pManager, SIGNAL(sig_receiveMessage(QString )), this, SLOT(slot_receiveMessage(QString)));
    connect(m_content, SIGNAL(sig_deleteMesssage(QString )), this, SLOT(slot_receiveMessage(QString)));

    //接收到服务器发送过的消息连接槽
}

Cos_GroupChat::~Cos_GroupChat()
{

}

void Cos_GroupChat::ppppp()
{
    QString pHtml = pTextEdit1->toPlainText();
    QString html = QString("appendMyMessage(%1, '%2');scrollBottom();").arg("'you'").arg(pHtml);
    m_pView->page()->runJavaScript(html);
}

void Cos_GroupChat::ppppp1()
{
    QString pHtml = pTextEdit2->toPlainText();
    qDebug() << pHtml;
    QString html = QString("appendOtherMessage(%1, '%2');scrollBottom();").arg("'me'").arg(pHtml);
    m_pView->page()->runJavaScript(html);
}

bool Cos_GroupChat::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pView)
    {
        QWheelEvent *p = dynamic_cast<QWheelEvent*>(event);
        if (p)
        {
            return QWidget::eventFilter(watched, event);
        }
    }
    else if (watched == ui.m_textEdit_send)
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->key() == Qt::Key_Return)
            {
                slot_lineEditReturnpressed();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

QString Cos_GroupChat::getTextId(QString labelID)
{
    return labelID + "text";
}

QString Cos_GroupChat::getHeadId(QString labelID)
{
    return labelID + "head";
}

void Cos_GroupChat::SendMsgShow(QString msg, QString head)
{
    //HTML加载显示到消息框中
    QString html = QString("");
    sendDivID++;
    QString divID = QString("send%1").arg(sendDivID);
    QString textID = getTextId(divID);
    // QString divID = "send"+ sendDivID;
    html.append(QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div id=%1 class='message'><div class='divMyHead'>%2 </div><div id=%3 class='triangle-right right'>%4</div></div>\")").arg(divID).arg(head).arg(textID).arg(msg));
    m_pView->page()->runJavaScript(html);
    QString html2 = QString("scrollBottom();");
    m_pView->page()->runJavaScript(html2);
    //    m_timer->start( 30000 );
    pManager->sendMessage(msg);
    mp_idToMsg.insert(divID, msg);
}

void Cos_GroupChat::RevMsgShow(QString msg, QString head)
{
    //HTML加载显示到消息框中
    RecvDIvID++;
    QString divID = QString("recv%1").arg(RecvDIvID);
    QString textID = getTextId(divID);
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div id=%1 style='overflow:hidden;' class='message'><div class='divotherhead'>%2 </div><div id=%3 class='triangle-left left'>%4</div></div>\")").arg(divID).arg(head).arg(textID).arg(msg);

    m_pView->page()->runJavaScript(html);
    QString html2 = QString("scrollBottom();");
    m_pView->page()->runJavaScript(html2);
}

void Cos_GroupChat::slot_btnpicClicked()
{
    QString FilePath = QFileDialog::getOpenFileName();
    QFile file(FilePath);
    bool ok = file.open(QIODevice::ReadOnly);
    if (!ok) {
        return;
    }
    QString msg = QString("<img src=%1 />").arg(FilePath);
    //QString MyHead = QString("<img src=%1 width='30px' heigth='30px'/>").arg(FilePath);
    QString Msg = QString("<img src=qrc:/chatdemo/Msg/downloading.jpg/>");
    //QString otherhead = MyHead;
    SendMsgShow(msg, Myhead);
    RevMsgShow(Msg, otherhead);
}

void Cos_GroupChat::slot_receiveMessage(QString msgStr)
{
    RevMsgShow(msgStr, otherhead);
}

void Cos_GroupChat::slot_deleteMessage(QString divID)
{
    mp_idToMsg.remove(divID);
}

void Cos_GroupChat::on_pushButton_clicked()
{

}

void Cos_GroupChat::on_pushButton_2_clicked()
{

}

void Cos_GroupChat::clearLastMessage()
{
    QString divID = QString("recv%1").arg(sendDivID);
    //  QString divID = "recv"+ RecvDIvID;
    qDebug() << divID;
    QString html = QString("deleteLastMessage(\"%1\");").arg(divID);
    m_pView->page()->runJavaScript(html);
    sendDivID--;
}

void Cos_GroupChat::updateMessage()
{
    QString  msgtext = ui.m_textEdit_send->toPlainText();
    QString html = QString("");
    QString divID = QString("send%1").arg(sendDivID);
    QString textID = getTextId(divID);
    html.append(QString("updateMessage(\"%1\", \'%2\')").arg(textID).arg(msgtext));
    m_pView->page()->runJavaScript(html);
    //    m_timer->start( 30000 );
    QString html2 = QString("scrollBottom();");
    m_pView->page()->runJavaScript(html2);
}

void Cos_GroupChat::slot_lineEditReturnpressed()
{
    QString  msgtext = ui.m_textEdit_send->toPlainText();
    if (msgtext == NULL)
    {
        QMessageBox::warning(this, "错误", "不要发送空信息!");
        return;
    } /**自己发送的消息*/
    SendMsgShow(msgtext, Myhead);
    qDebug() << "msgtext:send:" << msgtext;

    /*if (msgtext == QString::fromUtf8("你好"))
    {
        RevMsgShow("请问有什么可以帮助你吗？", otherhead);
    }
    else if (msgtext == QString::fromUtf8("时间"))
    {
        RevMsgShow(QString("北京时间: %1").arg(QTime::currentTime().toString("hh:mm:ss")), otherhead);
    }*/
    ui.m_textEdit_send->clear();
}
