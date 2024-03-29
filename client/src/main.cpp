/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:17:01
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:17:01
 */
#include "data/word.h"
#include "tcpclient.h"
#include "windowmanager.h"
#include <QObject>

int main(int argc, char *argv[]) {
    //    Word::instance()._initWord();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Manager::instance().init();
    QObject::connect(Manager::instance().mw, &MainWindow::sendCloseAll, &a,
                     &QCoreApplication::quit);
    a.exec();
    return 0;
}
