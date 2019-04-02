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
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>

QT_BEGIN_NAMESPACE

class Ui_LoginDialogUi
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QtMaterialTextField *usernameLineEdit;
    QtMaterialTextField *passwordLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QtMaterialRaisedButton *loginPushBotton;
    QtMaterialRaisedButton *registerPushButton;
    QHBoxLayout *horizontalLayout;
    QtMaterialRadioButton *wordRadioButton;
    QtMaterialRadioButton *challengerRadioButton;

    void setupUi(QDialog *LoginDialogUi)
    {
        if (LoginDialogUi->objectName().isEmpty())
            LoginDialogUi->setObjectName(QStringLiteral("LoginDialogUi"));
        LoginDialogUi->setWindowModality(Qt::WindowModal);
        LoginDialogUi->resize(500, 400);
#ifndef QT_NO_STATUSTIP
        LoginDialogUi->setStatusTip(QStringLiteral(""));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        LoginDialogUi->setWhatsThis(QStringLiteral(""));
#endif // QT_NO_WHATSTHIS
        LoginDialogUi->setSizeGripEnabled(true);
        LoginDialogUi->setModal(true);
        gridLayoutWidget = new QWidget(LoginDialogUi);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(60, 120, 393, 231));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        usernameLineEdit = new QtMaterialTextField(gridLayoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(29);
        sizePolicy.setVerticalStretch(29);
        sizePolicy.setHeightForWidth(usernameLineEdit->sizePolicy().hasHeightForWidth());
        usernameLineEdit->setSizePolicy(sizePolicy);
        usernameLineEdit->setMinimumSize(QSize(4, 50));

        gridLayout->addWidget(usernameLineEdit, 1, 0, 1, 1);

        passwordLineEdit = new QtMaterialTextField(gridLayoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(passwordLineEdit->sizePolicy().hasHeightForWidth());
        passwordLineEdit->setSizePolicy(sizePolicy1);
        passwordLineEdit->setMinimumSize(QSize(0, 50));
        passwordLineEdit->setAutoFillBackground(true);

        gridLayout->addWidget(passwordLineEdit, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        loginPushBotton = new QtMaterialRaisedButton(gridLayoutWidget);
        loginPushBotton->setObjectName(QStringLiteral("loginPushBotton"));
        loginPushBotton->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(loginPushBotton);

        registerPushButton = new QtMaterialRaisedButton(gridLayoutWidget);
        registerPushButton->setObjectName(QStringLiteral("registerPushButton"));
        registerPushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(registerPushButton);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        wordRadioButton = new QtMaterialRadioButton(gridLayoutWidget);
        wordRadioButton->setObjectName(QStringLiteral("wordRadioButton"));

        horizontalLayout->addWidget(wordRadioButton);

        challengerRadioButton = new QtMaterialRadioButton(gridLayoutWidget);
        challengerRadioButton->setObjectName(QStringLiteral("challengerRadioButton"));

        horizontalLayout->addWidget(challengerRadioButton);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);


        retranslateUi(LoginDialogUi);

        QMetaObject::connectSlotsByName(LoginDialogUi);
    } // setupUi

    void retranslateUi(QDialog *LoginDialogUi)
    {
        LoginDialogUi->setWindowTitle(QApplication::translate("LoginDialogUi", "Dialog", Q_NULLPTR));
        loginPushBotton->setText(QApplication::translate("LoginDialogUi", "Login", Q_NULLPTR));
        registerPushButton->setText(QApplication::translate("LoginDialogUi", "Register", Q_NULLPTR));
        wordRadioButton->setText(QApplication::translate("LoginDialogUi", "word builder", Q_NULLPTR));
        challengerRadioButton->setText(QApplication::translate("LoginDialogUi", "challenger", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialogUi: public Ui_LoginDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LOGINDIALOG_UI_H
