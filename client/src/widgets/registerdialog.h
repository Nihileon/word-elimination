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
    //back to login dialog
    void backLogin();
    void showMainWindow();

signals:
    void toLogin();
    void toMainWindow();
    void sendUser(QVariant user);


public slots:
    void reg();


public:
//private:
    Ui::RegisterDialogUi* ui;
};

#endif // REGISTERDIALOG_H
