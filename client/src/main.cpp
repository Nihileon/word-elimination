#include "windowmanager.h"


int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    Manager::instance().init();
    return a.exec();
}
