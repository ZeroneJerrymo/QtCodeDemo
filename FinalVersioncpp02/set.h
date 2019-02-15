#ifndef SET_H
#define SET_H

#include<QMouseEvent>
#include"sysbutton.h"
#include <QDialog>

namespace Ui {
class set;
}

class set : public QDialog
{
    Q_OBJECT
    

public:
    explicit set(QWidget *parent = 0);
    void Icon_Init();
    void photo_Init();
    QStringList headList;                                           //Í·ÏñÁ´±í
    QStringList photoList;
    sysButton *btnMin;
    //sysButton *btnMax;
    sysButton *btnClose;
     ~set();
private:
    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

    bool isMove;

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
public slots:

    void submit_slot();
    void calcel_slot();
    void showMin();
    void showclose();
private:
    Ui::set *ui;
};


    

#endif // SET_H
