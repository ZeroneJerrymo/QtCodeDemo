#include "MytestDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MytestDemo w;
	w.show();
	return a.exec();
}
