
#include "testchnsysdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    testChnsysDialog w;
    w.show();

    return a.exec();
}
