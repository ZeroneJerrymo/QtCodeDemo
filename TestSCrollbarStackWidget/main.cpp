#include "mainwindow.h"
#include <QApplication>
#include "testtable.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testtable w;
    w.show();

    return a.exec();
}
