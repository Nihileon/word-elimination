#include "windowmanager.h"
#include "data/word.h"
#include <QObject>

int main(int argc, char* argv[]) {
    //    Word::instance()._initWord();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Manager::instance().init();
    QObject::connect(Manager::instance().mw, &MainWindow::sendCloseAll, &a, &QCoreApplication::quit);
    a.exec();
    return 0;
}
