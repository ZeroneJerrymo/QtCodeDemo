
#include <QApplication>
#include "cos_groupchat.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cos_GroupChat w;
    w.show();

    return a.exec();
}
