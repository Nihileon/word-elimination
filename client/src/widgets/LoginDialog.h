#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
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

signals:
    void sendUser(QVariant user);

private:
    Ui::LoginDialogUi * ui;

};

#endif // LOGINDIALOG_H
