#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialdialog.h>
#include "ui/LoginDialog_ui.h"
#include "ui/materialmessagebox.h"
#include "data/user.h"
#include "LoginDialog.h"
#include "RegisterDialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialogUi),
    msg(new MaterialMessageBox(this))
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    ui->challengerRadioButton->setChecked(true);
    ui->loginPushBotton->setShortcut(Qt::Key_Enter);
    ui->loginPushBotton->setDefault(true);
    ui->passwordLineEdit->setLabel("Password");
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->usernameLineEdit->setLabel("Username");
    ui->registerPushButton->setBackgroundMode(Qt::OpaqueMode);

    connect(ui->loginPushBotton,&QPushButton::clicked,this,&LoginDialog::checkPassword);
    connect(ui->registerPushButton,&QPushButton::clicked, this, &LoginDialog::showReg);
}


LoginDialog::~LoginDialog(){
    delete ui;
    delete reg;
}

void LoginDialog::checkPassword(){
    LoginInfo loginInfo;
    if(ui->challengerRadioButton->isChecked()){
        loginInfo.type = LoginInfo::CHALLENGER;
    }else if(ui->wordRadioButton->isChecked()){
        loginInfo.type = LoginInfo::WORD_BUILDER;
    }

    loginInfo.usr = ui->usernameLineEdit->text().toStdString();
    loginInfo.pwd = ui->passwordLineEdit->text().toStdString();

    auto isAccept= User::instance().isUser(loginInfo);
    if(isAccept == true){
        QVariant user;
        user.setValue(loginInfo);
        emit sendUser(user);
        showMainWindow();
    }else{
//        MaterialMessageBox *msg = new MaterialMessageBox(this);
        msg->setText("Login failed! \nPlease check your password or user type.");
        msg->showDialog();
    }
}

void LoginDialog::showReg(){
    this->hide();
    emit toReg();
}

void LoginDialog::showMainWindow(){
    this->hide();
    emit toMain();
}

