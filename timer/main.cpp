#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DigiFlip time;
//#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WINCE_WM)
//  time.showFullScreen();
//#else
    time.resize(320, 240);
    time.show();
//#endif

    return app.exec();
}
