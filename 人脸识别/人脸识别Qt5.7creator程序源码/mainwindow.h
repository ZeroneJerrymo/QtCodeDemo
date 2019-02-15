/*
 * 本程序由南邮通达设计
 * 暂未对外开发
 * 请勿传播
 * 技术问题请联系QQ570176391
 * 陈同学
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QTimerEvent>
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QProcess>
#include <QMessageBox>
#include <math.h>
#include "currtime.h"
#include "addpeople.h"
#include "file.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setStatusBar();    //设置状态栏
    ~MainWindow();
    virtual void timerEvent(QTimerEvent* event);


private slots:
    void on_Add_action_triggered();     //添加图库

    void on_dispose_action_triggered();

    void on_action_addcsv_triggered();

    void on_action_TrainnigModel_triggered();

    void on_action_FaceRecognition_triggered();

    void on_actionData_triggered();

    void on_action_use_triggered();

    void on_action_about_triggered();

private:
    Ui::MainWindow *ui;
    AddPeople addpeople;    //添加图库界面
    MyFILE file;  //文件操作
    QLabel *statusLabel1;    //状态栏运行时间图标

    int m_timerId; // 每个Timer有一个id
};

#endif // MAINWINDOW_H
