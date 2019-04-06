#include <QMessageBox>
#include <QAbstractAnimation>
#include <exception>
#include "data/user.h"
#include "ui/RegisterDialog_ui.h"
#include "RegisterDialog.h"
#include "LoginDialog.h"
#include <qtmaterialdialog.h>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QLabel>
RegisterDialog::RegisterDialog(QWidget* parent):QDialog (parent), ui(new Ui::RegisterDialogUi) {
    ui->setupUi(this);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    ui->challengerRadioButton->setChecked(true);

    ui->registerPushButton->setShortcut(Qt::Key_Enter);
    ui->passwordLineEdit->setLabel("Password");
    ui->usernameLineEdit->setLabel("Username");
    //    connect(ui->backPushBotton, &QPushButton::clicked, this, &RegisterDialog::back);
    connect(ui->registerPushButton, &QPushButton::clicked, this, &RegisterDialog::reg);
    connect(ui->backPushButton, &QPushButton::clicked, this, &RegisterDialog::backLogin);
}


RegisterDialog::~RegisterDialog(){
    delete ui;
}

void RegisterDialog::reg(){
    LoginInfo loginInfo;
//    switch (ui->characterComboBox->currentIndex()) {
//    case 0:
//        loginInfo.type = LoginInfo::WORD_BUILDER;
//        break;
//    case 1:
//        loginInfo.type = LoginInfo::CHALLENGER;
//        break;
//    }
    if(ui->challengerRadioButton->isChecked()){
        loginInfo.type = LoginInfo::CHALLENGER;
    }else if(ui->wordRadioButton->isChecked()){
        loginInfo.type = LoginInfo::WORD_BUILDER;
    }
    loginInfo.usr = ui->usernameLineEdit->text().toStdString();
    loginInfo.pwd = ui->usernameLineEdit->text().toStdString();
    // \TODO 处理空用户名的问题
    try {
        User::instance().insert(loginInfo);
        QVariant user;
        user.setValue(loginInfo);
        emit sendUser(user);
        showMainWindow();

    } catch (QSqlError& e) {
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
        ql->setText("Your username has been used!\n"
                    "Please login or change your username.");
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

void RegisterDialog::backLogin(){

    emit toLogin();
    this->hide();
}

void RegisterDialog::showMainWindow()
{
    this->hide();
    emit toMainWindow();
}
