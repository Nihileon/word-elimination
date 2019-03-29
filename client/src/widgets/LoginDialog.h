#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include "registerdialog.h"
namespace Ui {
class LoginDialogUi;
};

class LoginDialog: public QDialog{

    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();
    //jump to register dialog
    void showReg();
    void showMainWindow();

public slots:
    void checkPassword();
    void showLogin();

signals:
    void sendUser(QVariant user);
    void toReg();
    void toMain();

private:
    Ui::LoginDialogUi * ui;
    RegisterDialog* reg;

};

#endif // LOGINDIALOG_H
