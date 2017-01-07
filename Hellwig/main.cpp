#include "hellwig.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Hellwig w;
	w.show();
	return a.exec();
}
