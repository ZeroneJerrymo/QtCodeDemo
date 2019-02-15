#ifndef MOVIEPUSHBUTTON_H
#define MOVIEPUSHBUTTON_H

#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
class MoviePushbutton : public QWidget
{
    Q_OBJECT
public:
    explicit MoviePushbutton(QWidget *parent = nullptr);
    void initUi();
    void timerEvent(QTimerEvent *event);
signals:

public slots:
    void slot_startLoad();
private:
    QStackedLayout* stackLayout;
    QPushButton* pb_btn;
    QLabel* lb_moive;

    QMovie* pmovie;
};



//#include "main.moc"

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    QWidget window;
//    TOOTBtn btn("zoe.gif", "Test Btn....", &window);
//    btn.move(100,100);
//    window.show( );
//    window.resize(640,400);
//    window.setWindowTitle("TOOTzoe.com Animating Button Test....");
//    QObject::connect(&btn, SIGNAL(clicked()), &window, SLOT(close()));

//    return app.exec();
//}


#endif // MOVIEPUSHBUTTON_H
