#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Digits.h"
#include <QMainWindow>

class DigiFlip : public QMainWindow
{
    Q_OBJECT

public:
    DigiFlip(QWidget *parent = 0);
    /*Real-time updates*/
    void updateTime();
    /*Switch transition mode*/
    void switchTransition(int delta);

protected:
    void resizeEvent(QResizeEvent*);
    /*Timer event,receive timer events */
    void timerEvent(QTimerEvent*);
    /* Get key press event */
    void keyPressEvent(QKeyEvent *event);
private slots:
    void chooseSlide();
    void chooseFlip();
    void chooseRotate();

private:
    QBasicTimer m_ticker;
    Digits *m_hour;
    Digits *m_minute;
};

#endif // MAINWINDOW_H
