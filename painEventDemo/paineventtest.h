#ifndef PAINEVENTTEST_H
#define PAINEVENTTEST_H

#include <QWidget>

class painEventTest : public QWidget
{
    Q_OBJECT
public:
    explicit painEventTest(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);

signals:

public slots:
    void slot_setbackcolor();

private:
    QColor pcolor;
    QPixmap pixmap ;

};

#endif // PAINEVENTTEST_H
