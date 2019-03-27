#include <QApplication>
#include "widgets/LoginDialog.h"
#include "widgets/mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  LoginDialog d;
  if (d.exec() != QDialog::Accepted) {
    return 1;
  }
  w.show();

  return a.exec();
}
