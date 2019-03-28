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

public slots:
    void checkPassword();
    void showReg();

signals:
    void sendUser(QVariant user);
    void showRegister();

private:
    Ui::LoginDialogUi * ui;
    RegisterDialog* reg;

};

#endif // LOGINDIALOG_H
