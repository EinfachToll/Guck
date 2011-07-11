#include <QApplication>

#include "bildi.hh"

 int main(int argc, char *argv[])
 {
	 QApplication app(argc, argv);
	 QStringList* args = new QStringList(app.arguments());
	 Bildi bildi(0, args);
	 bildi.show();
	 return app.exec();
 }
