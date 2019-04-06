#include <QLabel>
#include <QMessageBox>
#include <QObject>
#include "ui/LoginDialog_ui.h"
#include "LoginDialog.h"
#include "data/user.h"
#include "registerdialog.h"
#include <qtmaterialdialog.h>
#include <QVBoxLayout>
#include <QColorDialog>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialogUi)/*,reg(new RegisterDialog)*/
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
    ui->usernameLineEdit->setLabel("Username");
    ui->registerPushButton->setBackgroundMode(Qt::OpaqueMode);
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

        //\TODO: move this code to _ui.h
        QtMaterialDialog *msg = new QtMaterialDialog;
        msg->setParent(this);
        QWidget *dialogWidget = new QWidget;
        QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
        dialogWidget->setLayout(dialogWidgetLayout);
        QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
        QLabel* ql = new QLabel;
        QFont ft;
        ft.setPointSize(14);
        ql->setFont(ft);
        ql->setText("Login failed! \nPlease check your password or user type.");
        dialogWidgetLayout->addWidget(ql);
        dialogWidgetLayout->setAlignment(ql, Qt::AlignBottom| Qt::AlignCenter);
        dialogWidgetLayout->addWidget(closeButton);
        dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom| Qt::AlignCenter);
        closeButton->setMaximumWidth(150);
        QVBoxLayout *dialogLayout = new QVBoxLayout;
        msg->setWindowLayout(dialogLayout);
        dialogWidget->setMinimumHeight(150);
        dialogWidget->setMinimumWidth(300);
        dialogLayout->addWidget(dialogWidget);
        connect(closeButton, SIGNAL(pressed()), msg, SLOT(hideDialog()));
        msg->showDialog();
        msg->show();
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

