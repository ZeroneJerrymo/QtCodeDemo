#include "chnsysdialog.h"
#include "chnsystitlewidget.h"
#include <QFile>
#include <QPainter>
#include <QStyleOption>
ChnsysAbstractDialog::ChnsysAbstractDialog(QWidget *parent)
{

}


ChnsysDialog::ChnsysDialog(QWidget *parent) : ChnsysAbstractDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);

    m_title = new ChnsysTitleWidget(this);
    m_title->setFixedHeight(30);
    //m_title->setStyleSheet("background-color:transparent");
    m_centerWidget = new QWidget(this);
    InitDialogUI();
    retranlateUI();
    m_centerWidget->setObjectName("ChnsysDialog");
    //this->setStyleSheet("#ChnsysDialog{background-color:white}");
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_title);
    mainLayout->addWidget(m_centerWidget);
    this->setContentsMargins(1,1,1,1);
    this->setLayout(mainLayout);
    //LoadStyleSteetFile();
}

void ChnsysDialog::InitDialogUI()
{

}

void ChnsysDialog::retranlateUI()
{

}

void ChnsysDialog::LoadStyleSteetFile()
{
    QString qss;
    QFile qssFile("D:/workSpace/Demo/build-ChnsysDialog-Desktop_Qt_5_9_6_MSVC2015_32bit-Debug/debug/chsysCos.qss");  //////":/qss/css.qss"//////
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        this->setStyleSheet(qss);
        qssFile.close();
    }
}

void ChnsysDialog::paintEvent()
{
     QStyleOption opt;
     opt.initFrom(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);//绘制样式
}

