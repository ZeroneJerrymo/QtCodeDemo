#include "qrcodewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    Q_INIT_RESOURCE(qrencode);
    QApplication a(argc, argv);
    QRCodeWidget w;
    w.show();

    return a.exec();
}
