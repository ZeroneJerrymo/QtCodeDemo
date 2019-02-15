/******************************************************************
 Copyright (C) 2016 - All Rights Reserved by
 重庆重邮汇测通信技术有限公司
 文 件 名 : chatwindow.cpp --- ChatWindow
 作 者    : Niyh
 编写日期 : 2016/12/8
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
 倪又华    2016/12/8    1.0.0.0 1     文件创建
*******************************************************************/
#include "chatwindow.h"
#include "ui_chatwindow.h"
#include "myapp.h"

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ChatWindow::on_pushButton_4_clicked()
{
    ui->widgetChat->addItem(ui->textEditSnd->toPlainText(), qrand() % 2 + 1);
//    ui->widgetChat->setCurrItem(ui->widgetChat->);
}

void ChatWindow::on_pushButton_3_clicked(bool checked)
{
    Q_UNUSED(checked)
//    ui->widgetChat->clear();
}

void ChatWindow::on_checkBox_clicked(bool checked)
{
    MyApp::m_bDrawBg = checked;
    ui->widgetChat->render();
}
