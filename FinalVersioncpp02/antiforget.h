#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDate>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <stdlib.h>
#include <QIODevice>
#include <QFileInfo>
#include <QTextBlock>
#include <QTextDocument>

namespace Ui {
class widget;
}

class Widget2 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget2(QWidget *parent = 0);
    ~Widget2();

private slots:
    //void on_calendarButton_clicked();
    void showcalendar();//在lineedit中显示所选择的日期
    void onsave();//保存所填备忘内容
    void on_cancelButton_clicked();//清除所填内容

private:
    Ui::widget *ui;

    //void setdate();
    //void createFile(QString str);
};

#endif // WIDGET_H
