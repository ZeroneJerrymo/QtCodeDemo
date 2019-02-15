/******************************************************************
 Copyright (C) 2016 - All Rights Reserved by
 重庆重邮汇测通信技术有限公司
 文 件 名 : chatwindow.h --- ChatWindow
 作 者    : Niyh
 编写日期 : 2016/12/8
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
 倪又华    2016/12/8    1.0.0.0 1     文件创建
*******************************************************************/
#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QPushButton>

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked(bool checked);

    void on_checkBox_clicked(bool checked);

private:
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
