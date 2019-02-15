#include "chatbubble.h"
#include "chatwindow.h"
#include <QApplication>

//using namespace BubbleWidget;

#define MAX 100

//#define TEST_PLAN2

int main(int argc,char** argv)
{
    QApplication app(argc,argv);


#ifdef TEST_PLAN1
    QStringList days;
    days << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday" << "Saturday" << "Sunday";
    foreach(const QString& str,days)
    {
        win.addItem(str);
    }
#endif

#ifdef TEST_PLAN2
    BubbleList win;
    for(int i = 0;i < MAX ; i++)
    {
        win.addItem(QObject::tr("Item NumbeNumberNumberr 张二娃 %1").arg(i+1), qrand() % 2 + 1);
    }
    win.resize(QSize(400, 400));
    win.show();
    win.setCurrItem(100);
#else
    ChatWindow w;
    w.show();
#endif

    return app.exec();
}
