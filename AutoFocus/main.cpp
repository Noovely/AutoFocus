#include "AutoFocus.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoFocus w;
	w.show();
	return a.exec();
}
