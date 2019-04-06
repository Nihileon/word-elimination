#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QVariant>

namespace Ui {
    class RegisterDialogUi;
}

class RegisterDialog: public QDialog{
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

signals:
    void toLogin();
    void toMainWindow();
    void sendUser(QVariant user);

public slots:

private slots:
    void reg();
    //back to login dialog
    void backLogin();
    void showMainWindow();

//public:
private:
    Ui::RegisterDialogUi* ui;
};

#endif // REGISTERDIALOG_H
