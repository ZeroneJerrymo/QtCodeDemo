#include "widget.h"
#include <QHBoxLayout>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QPushButton>
#include <QSplitter>
#include <QApplication>
#include <QWebEngineSettings>
#include <QPlainTextEdit>
CChatMessageWidget::CChatMessageWidget(QWidget *parent)
    : QWidget(parent)
{
//    QSplitter *sp = new QSplitter(Qt::Horizontal, this);
//    sp->setHandleWidth(10);
    m_pView = new QWebEngineView(this);
    m_pView->installEventFilter(this);

    QWebEnginePage *pPage = new QWebEnginePage(this);
    m_pView->setPage(pPage);

//    sp->addWidget(m_pView);

//    QWidget *p = new QWidget(this);
//    sp->addWidget(p);
//    p->setStyleSheet("background-color: #ff0000;");

    pPage->setUrl(QUrl("D:/workSpace/Demo/web/messageBox.html"));

    QVBoxLayout *pMai = new QVBoxLayout;
    pMai->addWidget(m_pView);

    this->setLayout(pMai);

    QPushButton *pp = new QPushButton("add me" ,this);
    connect(pp, SIGNAL(clicked()), this, SLOT(ppppp()));

    QPushButton *pp1 = new QPushButton("add other", this);
    connect(pp1, SIGNAL(clicked()), this, SLOT(ppppp1()));

     pTextEdit1 = new  QTextEdit(this);
     pTextEdit2= new  QTextEdit(this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(pp1);
    buttonLayout->addWidget(pp);
    pTextEdit1->setMinimumHeight(200);
    pTextEdit2->setMinimumHeight(200);

    QHBoxLayout *textEditLayout = new QHBoxLayout;
    textEditLayout->addWidget(pTextEdit1);
    textEditLayout->addWidget(pTextEdit2);

    pMai->addLayout(buttonLayout);
    pMai->addLayout(textEditLayout);
}

CChatMessageWidget::~CChatMessageWidget()
{

}
#include <QTextEdit>
#include <QWheelEvent>
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
//            .arg("msgxasx").arg(QStringLiteral("込込込込込込込込込込亜込込込込込込亜込込"));
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
    return QWidget::eventFilter(watched, event);
}
