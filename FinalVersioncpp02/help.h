#ifndef HELP_H
#define HELP_H
#include <QTimer>
#include <string>
#include <QDialog>
#include"sysbutton.h"
#include <QTextCodec>
#include<QMouseEvent>

namespace Ui {
class Help;
}

class help : public  QDialog
{
    Q_OBJECT
    
public:
    explicit help(QWidget *parent = 0);
    sysButton *btnMin;
    //sysButton *btnMax;
    sysButton *btnClose;
    QTextCodec *coder;
    ~help();


protected slots:
       void TimeOut();

private slots:

       void showMin();
       void showclose();

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;
    bool isMove;

    QTimer *timer;
    std::string temp_str;
    int pos1;
    Ui::Help *ui;



};

#endif // HELP_H
