#ifndef TESTBROADERWIDGET_H
#define TESTBROADERWIDGET_H
#include "cborderwidget.h"
#include <QWidget>

namespace Ui {
class testBroaderWidget;
}

class testBroaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit testBroaderWidget(QWidget *parent = 0);
    ~testBroaderWidget();

protected:
    //void paintEvent(QPaintEvent *event)  ;
private:
    Ui::testBroaderWidget *ui;
};

#endif // TESTBROADERWIDGET_H
