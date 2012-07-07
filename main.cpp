#include "qonsole.h"
#include "mainWindow.h"

int main(int argc, char* argv[]) {
   QApplication app(argc, argv);
   mainWindow win;
   win.setWindowTitle("Koditor");
   win.show();



   return app.exec();
}

