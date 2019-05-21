/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:45
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:45
 */
#include <exception>
#include <QMessageBox>
#include <QAbstractAnimation>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>
#include <qtmaterialdialog.h>
#include "data/user.h"
#include "ui/RegisterDialog_ui.h"
#include "ui/materialmessagebox.h"
#include "RegisterDialog.h"
#include "LoginDialog.h"

RegisterDialog::RegisterDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::RegisterDialogUi),
    msg(new MaterialMessageBox(this))
{
    ui->setupUi(this);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    ui->challengerRadioButton->setChecked(true);
    ui->registerPushButton->setShortcut(Qt::Key_Enter);
    ui->passwordLineEdit->setLabel("Password");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->usernameLineEdit->setLabel("Username");

    connect(ui->registerPushButton, &QPushButton::clicked, this, &RegisterDialog::reg);
    connect(ui->backPushButton, &QPushButton::clicked, this, &RegisterDialog::backLogin);
}


RegisterDialog::~RegisterDialog(){
    delete ui;
}

void RegisterDialog::reg(){
    LoginInfo loginInfo;
    if(ui->challengerRadioButton->isChecked()){
        loginInfo.type = LoginInfo::CHALLENGER;
    }else if(ui->wordRadioButton->isChecked()){
        loginInfo.type = LoginInfo::WORD_BUILDER;
    }
    loginInfo.usr = ui->usernameLineEdit->text().toStdString();
    loginInfo.pwd = ui->passwordLineEdit->text().toStdString();
    // \TODO 处理空用户名的问题
    qDebug() << "reg";
    if(User::instance().insert(loginInfo)){

        QVariant user;
        user.setValue(loginInfo);
        emit sendUser(user);
        showMainWindow();

    } else {
//        MaterialMessageBox *msg = new MaterialMessageBox(this);
        msg->setText("Your username has been used!\n"
                     "Please login or change your username.");
        msg->showDialog();
    }
}

void RegisterDialog::backLogin(){
    emit toLogin();
    this->hide();
}

void RegisterDialog::showMainWindow(){
    this->hide();
    emit toMainWindow();
}
