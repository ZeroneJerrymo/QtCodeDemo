#include "snake.h"
#include "ui_snake.h"
#include <QPainter>
#include <QMessageBox>
SnakeGame::SnakeGame(){
    footlen=30;
    linefg=1;
    this->resize(800,600);
    coder=QTextCodec::codecForName("utf-8");
    qsrand(QTime::currentTime().msec());
    snake.push_back(getNewFood());
    food=getNewFood();
    oldfood=food;
    snakespeed=200;
    speedtext=new QLabel(this);
    speedtext->setText(coder->toUnicode("speed:     "));
    speedtext->move(630,50);
    speedtext->show();
    speedtext1=new QLabel(this);
    speedtext1->setText(coder->toUnicode("按space键开始/暂停"));
    speedtext1->move(630,70);
    speedtext1->show();
    speednum=new QLabel(this);
    speednum->setText(QString::number(snakespeed/50)+"  ");
    speednum->move(707,50);
    lenthtext=new QLabel();
    timer = new QTimer();
    timer->setInterval(snakespeed);
    timer->stop();

    dire=D_RIGHT;
    maxlen=3;
    connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    connect(timer,SIGNAL(timeout()),this,SLOT(snakeMove()));
}
SnakeGame::~SnakeGame(){
    delete timer;
    delete food;
    delete speedtext;
    delete speednum;
}
void SnakeGame::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_Up:
            if(dire==D_UP) speed();
            else if(dire!=D_DOWN)
                dire=D_UP;break;
        case Qt::Key_Down:
            if(dire==D_DOWN) speed();
            else if(dire!=D_UP)
                dire=D_DOWN;break;
        case Qt::Key_Left:
            if(dire==D_LEFT) speed();
            else if(dire!=D_RIGHT)
                dire=D_LEFT;break;
        case Qt::Key_Right:
            if(dire==D_RIGHT) speed();
            else if(dire!=D_LEFT)
                dire=D_RIGHT;break;
        case Qt::Key_P:linefg-=1;break;
        case Qt::Key_Space:timefg?(timer->stop(),timefg=0):(timer->start(),timefg=1);break;
        case Qt::Key_W:
            if(snakespeed-50>0){
                timer->setInterval(snakespeed-=50);
                speednum->setText(QString::number(snakespeed/50));
            }
            break;
        case Qt::Key_Q:
            if(snakespeed+50<2000){
                timer->setInterval(snakespeed+=50);
                speednum->setText(QString::number(snakespeed/50));
            }
            break;
    }
}
void SnakeGame::speed(){
    snakeMove();
    //snakeMove();
    //snakeMove();
}
void SnakeGame::paintEvent(QPaintEvent*){
    if(linefg){
        QPainter qp(this);
        for(int x=30;x<601;x+=30){
            qp.drawLine(x,0,x,600);
            qp.drawLine(0,x,600,x);
        }
    }
}
bool SnakeGame::snakeDie(int x,int y){
    if(!(x>=0 && x<(this->width()-200) && y>=0 && y<this->height()))
    {
        return 1;
    }
    if(snake.length()>3){
        int i=2;
        while(i<snake.length()){
            if(x==snake[i]->x()&&y==snake[i]->y())
                return 1;
            ++i;
        }
    }
    return 0;
}
void SnakeGame::snakeMove(){
    int oldx,sx=(snake[0]->x());
    int oldy,sy=(snake[0]->y());
    oldx=sx;
    oldy=sy;
    switch(dire){
        case D_UP:sy-=footlen;break;
        case D_DOWN:sy+=footlen;break;
        case D_LEFT:sx-=footlen;break;
        case D_RIGHT:sx+=footlen;break;
    }
    if(snakeDie(sx,sy))
        this->close();
    snake[0]->move(sx,sy);
    if(sx==food->x() && sy==food->y()){
        snake.push_back(food);
        food=getNewFood();
    }
    int i=1;
    while(i<snake.length()){

        sx=snake[i]->x();
        sy=snake[i]->y();
        snake[i]->move(oldx,oldy);
        sx^=oldx^=sx^=oldx;
        sy^=oldy^=sy^=oldy;
        ++i;
    }
    if(oldfood!=food){
        oldfood->move(oldx,oldy);
        oldfood=food;
    }
    if(maxlen==snake.length()){
        QMessageBox msg;
        msg.setText(coder->toUnicode("Passed,going on?"));
        msg.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        timer->stop();
        if(msg.exec()==QMessageBox::No)
            this->close();
        else
            timer->start();
        maxlen*=2;
    }
}
QLabel* SnakeGame::getNewFood(){
    food=new QLabel(this);
    food->resize(footlen-6,footlen-6);
    food->setAutoFillBackground(true);
    food->setPalette(QPalette(QColor(qrand()%255,qrand()%255,qrand()%255)));
    int x=this->width()-footlen-200;
    //int y=this->height()-footlen;
    food->move(qrand()%x/footlen*footlen+3,qrand()%x/footlen*footlen+3);
    qDebug("%d %d",food->x(),food->y());
    food->show();
    return food;
}

