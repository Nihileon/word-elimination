#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include "RegisterDialog.h"
namespace Ui {
class LoginDialogUi;
};

class LoginDialog: public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);
    //jump to register dialog
    ~LoginDialog();

signals:
    void sendUser(QVariant user);
    void toReg();
    void toMain();

public slots:


private slots:
    void checkPassword();
    void showReg();
    void showMainWindow();

private:
    Ui::LoginDialogUi * ui;
    RegisterDialog* reg;

};

#endif // LOGINDIALOG_H
