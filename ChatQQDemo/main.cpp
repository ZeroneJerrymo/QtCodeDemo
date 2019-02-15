
#include <QApplication>
#include "cchatmessagewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CChatMessageWidget w;
    w.show();

    return a.exec();
}
