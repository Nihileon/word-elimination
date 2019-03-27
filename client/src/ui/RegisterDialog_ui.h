/********************************************************************************
** Form generated from reading UI file 'RegisterDialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef REGISTERDIALOG_UI_H
#define REGISTERDIALOG_UI_H

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

class Ui_RegisterDialogUi
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *backPushBotton;
    QPushButton *registerPushButton;
    QComboBox *characterComboBox;

    void setupUi(QDialog *RegisterDialogUi)
    {
        if (RegisterDialogUi->objectName().isEmpty())
            RegisterDialogUi->setObjectName(QStringLiteral("RegisterDialogUi"));
        RegisterDialogUi->resize(400, 300);
        formLayoutWidget = new QWidget(RegisterDialogUi);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(140, 110, 204, 71));
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
        backPushBotton = new QPushButton(formLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));

        horizontalLayout->addWidget(backPushBotton);

        registerPushButton = new QPushButton(formLayoutWidget);
        registerPushButton->setObjectName(QStringLiteral("registerPushButton"));

        horizontalLayout->addWidget(registerPushButton);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout);

        characterComboBox = new QComboBox(RegisterDialogUi);
        characterComboBox->setObjectName(QStringLiteral("characterComboBox"));
        characterComboBox->setGeometry(QRect(120, 20, 191, 22));

        retranslateUi(RegisterDialogUi);

        QMetaObject::connectSlotsByName(RegisterDialogUi);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialogUi)
    {
        RegisterDialogUi->setWindowTitle(QApplication::translate("RegisterDialogUi", "Dialog", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("RegisterDialogUi", "username", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("RegisterDialogUi", "password", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("RegisterDialogUi", "Back", Q_NULLPTR));
        registerPushButton->setText(QApplication::translate("RegisterDialogUi", "Register", Q_NULLPTR));
        characterComboBox->clear();
        characterComboBox->insertItems(0, QStringList()
         << QApplication::translate("RegisterDialogUi", "WordBuilder", Q_NULLPTR)
         << QApplication::translate("RegisterDialogUi", "Challenger", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class RegisterDialogUi: public Ui_RegisterDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // REGISTERDIALOG_UI_H
