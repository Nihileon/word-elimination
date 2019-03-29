#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H
#include <QDialog>
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

public slots:
    void reg();
    void showReg();

signals:
    void toLogin();
    void toMainWindow();

public:
//private:
    Ui::RegisterDialogUi* ui;
};

#endif // REGISTERDIALOG_H
