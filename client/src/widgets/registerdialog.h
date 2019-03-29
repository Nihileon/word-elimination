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
public slots:
    void reg();
    void back();

signals:

public:
//private:
    Ui::RegisterDialogUi* ui;
};

#endif // REGISTERDIALOG_H
