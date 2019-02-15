#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QObject>
#include <QString>
#include <QProcess>
#include <QFileDialog>
#include <QtDebug>
#include "snake.h"
#include "yoajiang.h"
#include "antiforget.h"

namespace Ui {
class add;
}


class add : public QDialog
{
    Q_OBJECT

public:
    explicit add(QWidget *parent = 0);
    ~add();
    //static QString addr[4];

private slots:
    void on_pushButton_qqcom_clicked();//打开腾讯网

    void on_pushButton_taobao_clicked();//打开淘宝网

    void on_pushButton_sina_clicked();//打开新浪网

    void on_pushButton_baidu_clicked();//打开百度网

    void on_pushButton_NotePad_clicked();//打开备忘录

    void on_pushButton_IE_clicked();//打开IE浏览器

    void on_pushButton_QQ_clicked();//打开QQ

    void on_pushButton_QT_clicked();//打开QT

    void on_pushButton_DVD_clicked();//打开播放器

    void on_pushButton_snake_clicked();//打开贪吃蛇游戏

    void on_pushButton_yaojiang_clicked();//打开摇奖游戏

private:
    Ui::add *ui;
    void createpathdir();//创建本地软件打开路径文件夹
    void createdatedir();//创建备忘事件路径文件夹
};

#endif // ADD_H
