#include <QApplication>
#include "widgets/LoginDialog.h"
#include "widgets/mainwindow.h"
#include "widgets/registerdialog.h"
#include <QObject>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  LoginDialog l;
  RegisterDialog r;
  auto status = l.exec();
    QObject::connect(&l, &LoginDialog::showRegister, &r,&RegisterDialog::show);
    QObject::connect(&r, &RegisterDialog::showLogin, &l, &LoginDialog::exec);
  if (status != QDialog::Accepted) {
    return 1;
  }
  w.show();

  return a.exec();
}
