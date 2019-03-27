/********************************************************************************
** Form generated from reading UI file 'logindialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LOGINDIALOG_UI_H
#define LOGINDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialogUi
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *loginPushBotton;
    QPushButton *registerPushButton;
    QComboBox *userComboBox;

    void setupUi(QDialog *LoginDialogUi)
    {
        if (LoginDialogUi->objectName().isEmpty())
            LoginDialogUi->setObjectName(QStringLiteral("LoginDialogUi"));
        LoginDialogUi->resize(400, 300);
        formLayoutWidget = new QWidget(LoginDialogUi);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(130, 190, 230, 81));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        usernameLabel = new QLabel(formLayoutWidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameLineEdit = new QLineEdit(formLayoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameLineEdit);

        passwordLabel = new QLabel(formLayoutWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(formLayoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordLineEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        loginPushBotton = new QPushButton(formLayoutWidget);
        loginPushBotton->setObjectName(QStringLiteral("loginPushBotton"));

        horizontalLayout->addWidget(loginPushBotton);

        registerPushButton = new QPushButton(formLayoutWidget);
        registerPushButton->setObjectName(QStringLiteral("registerPushButton"));

        horizontalLayout->addWidget(registerPushButton);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);

        userComboBox = new QComboBox(LoginDialogUi);
        userComboBox->setObjectName(QStringLiteral("userComboBox"));
        userComboBox->setGeometry(QRect(130, 140, 221, 22));

        retranslateUi(LoginDialogUi);

        QMetaObject::connectSlotsByName(LoginDialogUi);
    } // setupUi

    void retranslateUi(QDialog *LoginDialogUi)
    {
        LoginDialogUi->setWindowTitle(QApplication::translate("LoginDialogUi", "Dialog", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("LoginDialogUi", "Username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("LoginDialogUi", "password", Q_NULLPTR));
        loginPushBotton->setText(QApplication::translate("LoginDialogUi", "Login", Q_NULLPTR));
        registerPushButton->setText(QApplication::translate("LoginDialogUi", "Register", Q_NULLPTR));
        userComboBox->clear();
        userComboBox->insertItems(0, QStringList()
         << QApplication::translate("LoginDialogUi", "Word Builder", Q_NULLPTR)
         << QApplication::translate("LoginDialogUi", "Challenger", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class LoginDialogUi: public Ui_LoginDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGINDIALOG_UI_H
