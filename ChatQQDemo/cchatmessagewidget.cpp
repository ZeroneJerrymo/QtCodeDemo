#include "cchatmessagewidget.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QPushButton>
#include <QSplitter>
#include <QApplication>
#include <QWebEngineSettings>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QWheelEvent>
#include <QFileDialog>
#include <QMessageBox>
CChatMessageWidget::CChatMessageWidget(QWidget *parent)
    : QWidget(parent)
{

    Myhead = "<img src=qrc:/resource/myHead.png width='30px'heigth='30px'>";
    QString strHead = QString("qrc:/resource/otherHead.png");
    otherhead = QString ("<img src=%1 width='30px' heigth='30px'>").arg(strHead);

    m_pView = new QWebEngineView(this);
    m_pView->installEventFilter(this);

    QWebEnginePage *pPage = new QWebEnginePage(this);
    m_pView->setPage(pPage);


    pPage->setUrl(QUrl("qrc:/resource/messageBox.html"));

    QVBoxLayout *pMai = new QVBoxLayout;
    pMai->addWidget(m_pView);

    this->setLayout(pMai);

    QPushButton *pp = new QPushButton("Send" ,this);
    connect(pp, SIGNAL(clicked()), this, SLOT(slot_lineEditReturnpressed()));
    pp->setMinimumSize(120, 40);
    //    QPushButton *pp1 = new QPushButton("add other", this);
    //    connect(pp1, SIGNAL(clicked()), this, SLOT(ppppp1()));

    pTextEdit1 = new  QTextEdit(this);
    pTextEdit1->installEventFilter(this);//设置完后自动调用其eventFilter函数
    pTextEdit2= new  QTextEdit(this);
    pTextEdit2->setVisible(false);
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    //buttonLayout->addWidget(pp1);
    buttonLayout->addStretch();
    buttonLayout->addWidget(pp);
    pTextEdit1->setMinimumHeight(200);
    pTextEdit2->setMinimumHeight(200);

    QHBoxLayout *textEditLayout = new QHBoxLayout;
    textEditLayout->addWidget(pTextEdit1);
    textEditLayout->addWidget(pTextEdit2);
    pMai->addLayout(textEditLayout);

    pMai->addLayout(buttonLayout);
}

CChatMessageWidget::~CChatMessageWidget()
{

}

void CChatMessageWidget::ppppp()
{
    //    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'>\
    //                            <p class='divotherHead'>%1</p><p class='triangle-left left'>%2</p></div>\")")
    //            .arg("msgxasx").arg("hahaha<img src=qrc:/new/prefix1/00393[24x24x8BPP].gif/>hahahaha");

    QString pHtml = pTextEdit1->toPlainText();
    QString html = QString("appendMyMessage(%1, '%2');scrollBottom();").arg("'you'").arg(pHtml);
    m_pView->page()->runJavaScript(html);
}

void CChatMessageWidget::ppppp1()
{
    //    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'>\
    //                            <p class='divMyHead' >%1</p><p class='triangle-right right'>%2</p></div>\")")
    //            .arg("msgxasx").arg(QStringLiteral("哈哈哈哈哈哈哈哈哈哈啊哈哈哈哈哈哈啊哈哈"));
    QString pHtml = pTextEdit2->toPlainText();
    qDebug()<< pHtml;
    QString html = QString("appendOtherMessage(%1, '%2');scrollBottom();").arg("'me'").arg(pHtml);
    m_pView->page()->runJavaScript(html);
}

bool CChatMessageWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pView)
    {
        QWheelEvent *p = dynamic_cast<QWheelEvent*>(event);
        if (p)
        {
            return QWidget::eventFilter(watched, event);
        }
    }
    else if(watched == pTextEdit1)
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Return)
            {
                slot_lineEditReturnpressed();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void CChatMessageWidget::SendMsgShow(QString msg ,QString head)
{
    QString html = QString( "" );
    html.append(QString( "document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divMyHead'>%1 </p><p class='triangle-right right'>%2</p></div>\")" ) .arg( head ) .arg( msg ) );
    m_pView->page()->runJavaScript(html);
    //    m_timer->start( 30000 );
}

void CChatMessageWidget::RevMsgShow(QString msg,QString head)
{
    QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divotherhead'>%1 </p><p class='triangle-left left'>%2</p></div>\")") .arg(head) .arg(msg);
    m_pView->page()->runJavaScript(html);
}

void CChatMessageWidget::slot_btnpicClicked()
{
    QString FilePath = QFileDialog::getOpenFileName();
    QFile file( FilePath );
    bool ok = file.open( QIODevice::ReadOnly );
    if( !ok ) {
        return;
    }
    QString msg = QString("<img src=%1 />") .arg( FilePath );
    //QString MyHead = QString("<img src=%1 width='30px' heigth='30px'/>").arg(FilePath);
    QString Msg = QString ("<img src=qrc:/chatdemo/Msg/downloading.jpg/>");
    //QString otherhead = MyHead;
    SendMsgShow(msg,Myhead);
    RevMsgShow( Msg,otherhead);
}

void CChatMessageWidget::slot_lineEditReturnpressed()
{
    QString  msgtext = pTextEdit1->toPlainText();
    if( msgtext == NULL )
    {
        QMessageBox::warning( this , "warning","Can't send an empty msg!" );
        return;
    } /**自己发送的消息*/
    SendMsgShow( msgtext , Myhead );
    qDebug()<<"msgtext:send:"<< msgtext;

    if(msgtext == QString::fromUtf8( "你好" ))
    {
    RevMsgShow("请问有什么可以帮助你吗？" , otherhead );
    }
    else if(msgtext == QString::fromUtf8( "时间" ) )
    {
        RevMsgShow(QString("北京时间: %1") .arg( QTime::currentTime().toString( "hh:mm:ss" ) ), otherhead );
    }
    pTextEdit1->clear();
}
