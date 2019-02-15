#ifndef DIGITS_H
#define DIGITS_H
#include <QWidget>
#include <QtCore>


class Digits: public QWidget
{
    Q_OBJECT

public:

    /*Define three transition modes of the digital clock*/
    enum {
        Slide,
        Flip,
        Rotate
    };

    Digits(QWidget *parent);
    /*Set transition when time changed*/
    void setTransition(int tr);

    /*Get transition mode*/
    int transition() const;

    /*Set hours and minutes*/
    void setNumber(int n);

    /*Flip to next state*/
    void flipTo(int n);

protected:

    /*Draw the main frame of the digits area*/
    void drawFrame(QPainter *p, const QRect &rect);
    /*Draw the digits*/
    QPixmap drawDigits(int n, const QRect &rect);
    /*prepare the pixmap  */
    void preparePixmap();
    /*define a resize event*/
    void resizeEvent(QResizeEvent*);
    /*Paint the static state*/
    void paintStatic();
    /*Paint the slide state*/
    void paintSlide();
    /*Paint the flip state*/
    void paintFlip();
    /*Paint the rotate state*/
    void paintRotate();

    void paintEvent(QPaintEvent *event);
private:
    int m_number;//number to set to digits

    int m_transition;//transition mode(change effect)

    QPixmap m_pixmap;//current time pixmap

    QPixmap m_lastPixmap;//next state time pixmap

    QTimeLine m_animator;
    //used to animate a GUI control by calling a slot periodically
    //The timeline's duration describes for how long the animation will run
    //connect the frameChanged() signal to a suitable slot in the widget you wish to animate
};

#endif // DIGITS_H
