#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTime>
#include <QDebug>
#include <QScrollBar>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pView = new QWebEngineView(this);
    m_pView->installEventFilter(this);

    QWebEnginePage *pPage = new QWebEnginePage(this);
    m_pView->setPage(pPage);
    m_pView->page()->load(QUrl("qrc:/style.html"));

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(disTime()));
    m_timer->start(6000);
    disFlag = false;
    faceFormFlag = false;

    QVBoxLayout *pvlyt = new QVBoxLayout;
    pvlyt->addWidget(m_pView);
    ui->frame->setLayout(pvlyt);

    //connect(this, SIGNAL(toBottom()), this, SLOT(toViewBottom()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


// A show message
void MainWindow::AsendMsgShow(QString msg)
{
    QString html = QString("");

//    if (disFlag) {
//        QString time = QString("<center>%1</center>").arg(QTime::currentTime().toString("-- hh:mm --"));
//        html.append(QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"%1<div style='overflow:hidden;'><p class='triangle-right right'>%2</p></div>\")").arg(time).arg(msg));
//    }
//    else {
//        msg.replace( "[smail.png]", "<img src=qrc:/smail.png alt=???? align=center border=0>" );
//        msg.replace( "[ali.gif]", "<img src=qrc:/ali.gif alt=???? align=center border=0>" );
//        msg.append("<img src=file:///E:/qt/test/smail.png alt=???? with=24 height=24 align=center border=0>");
//        html.append(QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='triangle-right right'>%1</p></div>\")").arg(msg));
//    }

    msg.replace( "[smail.png]", "<img src=qrc:/smail.png alt=???? align=center border=0>" );
    msg.replace( "[ali.gif]", "<img src=qrc:/ali.gif alt=???? align=center border=0>" );

    m_pView->page()->runJavaScript(QString("ASendMsg('%1');").arg(msg));
    disFlag = false;
    m_timer->start(30000);
}

// B show message
void MainWindow::BSendMsgShow(QString msg)
{
    QString html = QString("");

    msg.replace( "[smail.png]", "<img src=qrc:/smail.png alt=???? align=center border=0>" );
    msg.replace( "[ali.gif]", "<img src=qrc:/ali.gif alt=???? align=center border=0>" );

    m_pView->page()->runJavaScript(QString("BSendMsg('%1');").arg(msg));
    disFlag = false;
    m_timer->start(30000);
}

// A send message button clicked
void MainWindow::on_pushButton_clicked()
{
    AsendMsgShow(ui->lineEdit->text());

    //
    if (ui->lineEdit->text() == QString("????"))
    {
        revMsgShow(QString("????,???????????????"));
    }
    else if (ui->lineEdit->text() == QString("???????"))
    {
        revMsgShow(QString("????????????%1").arg(QTime::currentTime().toString("hh:mm:ss")));
    }
}

// B send message button clicked
void MainWindow::on_pushButton_4_clicked()
{
    BSendMsgShow(ui->lineEdit_2->text());
}

void MainWindow::revMsgShow(QString msg)
{
    //QString html = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='triangle-left left'>%1</p></div>\")").arg(msg);
    QString html = QString("document.getElementById(\"content\").innerHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='triangle-left left'>%1</p></div>\")").arg(msg);
    m_pView->page()->runJavaScript(html);
}

void MainWindow::disTime()
{
    disFlag = true;
    m_timer->stop();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(faceFormFlag){
        disconnect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));
        m_faceForm->deleteLater();
        faceFormFlag = false;
        ui->verticalLayout->setStretch(0,10);
        return;
    }
    m_faceForm = new faceForm();
    faceFormFlag = true;
    ui->verticalLayout->insertWidget(1, m_faceForm, 4);
    ui->verticalLayout->setStretch(0, 6);
     connect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));
}


void MainWindow::addFace(QString text)
{
    ui->lineEdit->setText(ui->lineEdit->text()+text);
    ui->lineEdit->setFocus();
    disconnect(m_faceForm, SIGNAL(faceClicked(QString)), this, SLOT(addFace(QString)));
    m_faceForm->deleteLater();
    faceFormFlag = false;
    ui->verticalLayout->setStretch(0,10);
}


