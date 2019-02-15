#include "mainwindow.h"
#include <QApplication>
#include <QToolButton>
#include "testbroaderwidget.h"
#include "paineventtest.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testBroaderWidget w;
    w.show();
    QToolButton* pb_btn =new QToolButton(this);
    return a.exec();
}
