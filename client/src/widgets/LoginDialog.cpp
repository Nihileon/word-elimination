#include <QMessageBox>
#include <QObject>
#include "ui/LoginDialog_ui.h"
#include "LoginDialog.h"
#include "data/login.h"
#include "registerdialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialogUi)/*,reg(new RegisterDialog)*/
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    connect(ui->loginPushBotton,&QPushButton::clicked,this,&LoginDialog::checkPassword);
    connect(ui->registerPushButton,&QPushButton::clicked, this, &LoginDialog::showReg);

}


LoginDialog::~LoginDialog()
{
    delete ui;
    delete reg;
}

void LoginDialog::checkPassword(){
    LoginInfo loginInfo;
    switch (ui->userComboBox->currentIndex()) {
    case 0:
        loginInfo.type = LoginInfo::WORD_BUILDER;
        break;
    case 1:
        loginInfo.type = LoginInfo::CHALLENGER;
        break;
    }
    loginInfo.usr = ui->usernameLineEdit->text().toStdString();
    loginInfo.pwd = ui->passwordLineEdit->text().toStdString();
    QVariant user;
//    bool isAccept = false;
//    if(loginInfo.type == LoginInfo::WORD_BUILDER){
//        auto userPair = Login::instance().getWordBuilder(loginInfo);
//        if(userPair.first==Login::DEFAULT_STATUS){
//            user.setValue(userPair.second);
//            emit sendUser(user);
//            isAccept = true;
//        }
//    }else{
//        auto userPair = Login::instance().getChallenger(loginInfo);
//        if(userPair.first==Login::DEFAULT_STATUS){
//            user.setValue(userPair.second);
//            emit sendUser(user);
//            isAccept = true;
//        }
//    }
    auto isAccept= Login::instance().isUser(loginInfo);
    if(isAccept == true){
        user.setValue(loginInfo);
        emit sendUser(user);
        showMainWindow();
    }else{
        QMessageBox *msg = new QMessageBox;
        msg->setText("login failed, please check your password or user type");
        msg->setWindowModality(Qt::NonModal);
        msg->setStandardButtons(QMessageBox::Close);
        msg->exec();
    }
}




void LoginDialog::showReg(){
    this->hide();
    emit toReg();

}

void LoginDialog::showMainWindow()
{
    this->hide();
    emit toMain();
}

