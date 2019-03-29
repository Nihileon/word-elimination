#include <QMessageBox>
#include <QAbstractAnimation>
#include <exception>
#include "data/login.h"
#include "ui/RegisterDialog_ui.h"
#include "registerdialog.h"
#include "LoginDialog.h"
using namespace sqlite;
RegisterDialog::RegisterDialog(QWidget* parent):QDialog (parent), ui(new Ui::RegisterDialogUi) {
    ui->setupUi(this);
    //    connect(ui->backPushBotton, &QPushButton::clicked, this, &RegisterDialog::back);
    connect(ui->registerPushButton, &QPushButton::clicked, this, &RegisterDialog::reg);
    connect(ui->backPushBotton, &QPushButton::clicked, this, &RegisterDialog::backLogin);
}


RegisterDialog::~RegisterDialog(){
    delete ui;
}

void RegisterDialog::reg(){
    LoginInfo loginInfo;
    switch (ui->characterComboBox->currentIndex()) {
    case 0:
        loginInfo.type = LoginInfo::WORD_BUILDER;
        break;
    case 1:
        loginInfo.type = LoginInfo::CHALLENGER;
        break;
    }
    loginInfo.usr = ui->usernameLineEdit->text().toStdString();
    loginInfo.pwd = ui->usernameLineEdit->text().toStdString();
    // \TODO 处理空用户名的问题
    try {
        Login::instance().insert(loginInfo);
        showMainWindow();

    } catch (sqlite_exception& e) {
        QMessageBox *msg = new QMessageBox;
        msg->setText(QString("your uesrname has been used, please login or change your username: %1").arg(e.what()));
        msg->setWindowModality(Qt::NonModal);
        msg->setStandardButtons(QMessageBox::Close);
        msg->exec();
    }
}

void RegisterDialog::backLogin(){

    emit toLogin();
    this->hide();
}

void RegisterDialog::showMainWindow()
{
    this->hide();
    emit toMainWindow();
}
