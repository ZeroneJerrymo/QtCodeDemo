#include "mainwindow.h"
#include <QAction>
#include <QKeyEvent>
DigiFlip::DigiFlip(QWidget *parent): QMainWindow(parent)
{
    m_hour = new Digits(this);
    m_hour->show();
    m_minute = new Digits(this);
    m_minute->show();

    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::black);
    //Sets the color used for the given color role, in all color groups, to the specified solid color.

    setPalette(pal);

    m_ticker.start(1000, this);
    //Send a timer event every second

    QTime t = QTime::currentTime();
//    m_hour->setNumber(t.hour());
//    m_minute->setNumber(t.minute());
      m_hour->setNumber(t.minute());
      m_minute->setNumber(t.second());
    updateTime();

    QAction *slideAction = new QAction("&Slide", this);
    QAction *flipAction = new QAction("&Flip", this);
    QAction *rotateAction = new QAction("&Rotate", this);
    connect(slideAction, SIGNAL(triggered()), SLOT(chooseSlide()));
    connect(flipAction, SIGNAL(triggered()), SLOT(chooseFlip()));
    connect(rotateAction, SIGNAL(triggered()), SLOT(chooseRotate()));
#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WINCE_WM)
    menuBar()->addAction(slideAction);
    menuBar()->addAction(flipAction);
    menuBar()->addAction(rotateAction);
#else
    addAction(slideAction);
    addAction(flipAction);
    addAction(rotateAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    //Shows a context menu(right click)
#endif
}

void DigiFlip::updateTime() {
    QTime t = QTime::currentTime();
//    m_hour->flipTo(t.hour());
//    m_minute->flipTo(t.minute());
    m_hour->flipTo(t.minute());
    m_minute->flipTo(t.second());
    QString str = t.toString("hh:mm:ss");
    str.prepend(": ");
    if (m_hour->transition() == Digits::Slide)
        str.prepend("Slide");
    if (m_hour->transition() == Digits::Flip)
        str.prepend("Flip");
    if (m_hour->transition() == Digits::Rotate)
        str.prepend("Rotate");
    setWindowTitle(str);
}

void DigiFlip::switchTransition(int delta) {
    int i = (m_hour->transition() + delta + 3) % 3;
    m_hour->setTransition(i);
    m_minute->setTransition(i);
    updateTime();
}

void DigiFlip::resizeEvent(QResizeEvent*) {
    int digitsWidth = width() / 2;
    int digitsHeight = digitsWidth * 1.2;

    int y = (height() - digitsHeight) / 3;

    m_hour->resize(digitsWidth, digitsHeight);
    m_hour->move(0, y);

    m_minute->resize(digitsWidth, digitsHeight);
    m_minute->move(width() / 2, y);
}

void DigiFlip::timerEvent(QTimerEvent*) {
    updateTime();
}


void DigiFlip::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Right) {
        switchTransition(1);
        event->accept();
    }
    if (event->key() == Qt::Key_Left) {
        switchTransition(-1);
        event->accept();
    }
}

void DigiFlip::chooseSlide() {
    m_hour->setTransition(0);
    m_minute->setTransition(0);
    updateTime();
}

void DigiFlip::chooseFlip() {
    m_hour->setTransition(1);
    m_minute->setTransition(1);
    updateTime();
}

void DigiFlip::chooseRotate() {
    m_hour->setTransition(2);
    m_minute->setTransition(2);
    updateTime();
}
