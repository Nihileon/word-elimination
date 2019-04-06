/********************************************************************************
** Form generated from reading UI file 'registerdialog_ui.ui'
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
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialogUi
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QtMaterialTextField *usernameLineEdit;
    QtMaterialTextField *passwordLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QtMaterialRaisedButton *backPushButton;
    QtMaterialRaisedButton *registerPushButton;
    QHBoxLayout *horizontalLayout;
    QtMaterialRadioButton *wordRadioButton;
    QtMaterialRadioButton *challengerRadioButton;

    void setupUi(QDialog *RegisterDialogUi)
    {
        if (RegisterDialogUi->objectName().isEmpty())
            RegisterDialogUi->setObjectName(QStringLiteral("RegisterDialogUi"));
        RegisterDialogUi->resize(500, 400);
        gridLayoutWidget = new QWidget(RegisterDialogUi);
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
        backPushButton = new QtMaterialRaisedButton(gridLayoutWidget);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(backPushButton);

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


        retranslateUi(RegisterDialogUi);

        QMetaObject::connectSlotsByName(RegisterDialogUi);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialogUi)
    {
        RegisterDialogUi->setWindowTitle(QApplication::translate("RegisterDialogUi", "Dialog", Q_NULLPTR));
        backPushButton->setText(QApplication::translate("RegisterDialogUi", "Back", Q_NULLPTR));
        registerPushButton->setText(QApplication::translate("RegisterDialogUi", "Register", Q_NULLPTR));
        wordRadioButton->setText(QApplication::translate("RegisterDialogUi", "word builder", Q_NULLPTR));
        challengerRadioButton->setText(QApplication::translate("RegisterDialogUi", "challenger", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialogUi: public Ui_RegisterDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // REGISTERDIALOG_UI_H
