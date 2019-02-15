#ifndef SNAKE_H
#define SNAKE_H
/*贪吃蛇游戏的界面头文件*/
#include <QDialog>
#include <QList>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>
#include <QPaintEvent>
#include <QTextCodec>
enum Direction{D_UP,D_DOWN,D_LEFT,D_RIGHT};
class SnakeGame:public QDialog{
Q_OBJECT
private:
    QList<QLabel*> snake;
    QLabel *food,*oldfood,*speedtext,*speednum,*speedtext1;
    QLabel *lenthtext,*snakelenth;
    int footlen;
    QTimer *timer;
    QTextCodec *coder;
    Direction dire;
    int maxlen;
    bool linefg,timefg;
    int snakespeed;
public:
    SnakeGame();
    ~SnakeGame();
/*游戏功能*/
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent*);
    bool snakeDie(int,int);
/*获取新食物*/
    QLabel* getNewFood();
    void speed();
    //void ReGame();
public slots:
/*蛇移动，和定时器绑定*/
    void snakeMove();
};
#endif // SNAKE_H
