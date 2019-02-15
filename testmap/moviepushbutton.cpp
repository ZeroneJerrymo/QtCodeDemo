#include "moviepushbutton.h"

#include <QFileDialog>

MoviePushbutton::MoviePushbutton(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void MoviePushbutton::initUi()
{
   stackLayout = new QStackedLayout;
   pb_btn = new QPushButton("qisushu",this);
   lb_moive = new QLabel("qosushu",this);
   pmovie = new QMovie("D:\workSpace\Demo\testmap\22222.gif");

   pb_btn->setStyleSheet("QPushButton{border:none; color: rgb(255, 255, 255);background-color: rgb(245, 143, 32);border-radius:6px;font: 9pt \"黑体\";}");
   lb_moive->setStyleSheet("QPushButton{border:none; color: rgb(255, 255, 255);background-color: rgb(245, 143, 32);border-radius:6px;font: 9pt \"黑体\";}");
   pb_btn->setFocusPolicy(Qt::NoFocus);
    pb_btn->setFixedSize(QSize(100, 50));
    lb_moive->setFixedSize(QSize(32, 32));
    lb_moive->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lb_moive->setMovie(pmovie);
   stackLayout->addWidget(lb_moive);
   stackLayout->addWidget(pb_btn);

   stackLayout->setAlignment(this, Qt::AlignCenter);
   this->setLayout(stackLayout);

   connect(pb_btn, SIGNAL(clicked()), this, SLOT(slot_startLoad()));
}

void MoviePushbutton::timerEvent(QTimerEvent *event)
{
    pmovie->stop();
    lb_moive->clear();
    QPixmap px_right;
    lb_moive->resize(32, 32);
    //px_right.scaled(lb_moive->size(), Qt::KeepAspectRatio);
    px_right.load(QString(":/NewCos/Resources/merge_main.png"));
    lb_moive->setPixmap(px_right);
    stackLayout->setCurrentIndex(0);
}

void MoviePushbutton::slot_startLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/", tr("All Files (*.*)"));
       if (fileName.isEmpty())
            return;
    //stackLayout->setCurrentIndex(1);
    pmovie->start();
    this->startTimer(5000);
}
