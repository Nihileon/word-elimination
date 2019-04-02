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
    QHBoxLayout *horizontalLayout_4;
    QtMaterialRaisedButton *backPushBotton;
    QtMaterialRaisedButton *registerPushButton;
    QtMaterialTextField *passwordLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QtMaterialRadioButton *wordRadioButton;
    QtMaterialRadioButton *challengerRadioButton;
    QtMaterialTextField *usernameLineEdit;

    void setupUi(QDialog *RegisterDialogUi)
    {
        if (RegisterDialogUi->objectName().isEmpty())
            RegisterDialogUi->setObjectName(QStringLiteral("RegisterDialogUi"));
        RegisterDialogUi->resize(500, 400);
        gridLayoutWidget = new QWidget(RegisterDialogUi);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(100, 100, 311, 231));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        backPushBotton = new QtMaterialRaisedButton(gridLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));
        backPushBotton->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(backPushBotton);

        registerPushButton = new QtMaterialRaisedButton(gridLayoutWidget);
        registerPushButton->setObjectName(QStringLiteral("registerPushButton"));
        registerPushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(registerPushButton);


        gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        passwordLineEdit = new QtMaterialTextField(gridLayoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(passwordLineEdit->sizePolicy().hasHeightForWidth());
        passwordLineEdit->setSizePolicy(sizePolicy);
        passwordLineEdit->setMinimumSize(QSize(0, 50));
        passwordLineEdit->setAutoFillBackground(true);

        gridLayout->addWidget(passwordLineEdit, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        wordRadioButton = new QtMaterialRadioButton(gridLayoutWidget);
        wordRadioButton->setObjectName(QStringLiteral("wordRadioButton"));

        horizontalLayout_3->addWidget(wordRadioButton);

        challengerRadioButton = new QtMaterialRadioButton(gridLayoutWidget);
        challengerRadioButton->setObjectName(QStringLiteral("challengerRadioButton"));

        horizontalLayout_3->addWidget(challengerRadioButton);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        usernameLineEdit = new QtMaterialTextField(gridLayoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(29);
        sizePolicy1.setVerticalStretch(29);
        sizePolicy1.setHeightForWidth(usernameLineEdit->sizePolicy().hasHeightForWidth());
        usernameLineEdit->setSizePolicy(sizePolicy1);
        usernameLineEdit->setMinimumSize(QSize(4, 50));

        gridLayout->addWidget(usernameLineEdit, 1, 0, 1, 1);


        retranslateUi(RegisterDialogUi);

        QMetaObject::connectSlotsByName(RegisterDialogUi);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialogUi)
    {
        RegisterDialogUi->setWindowTitle(QApplication::translate("RegisterDialogUi", "Dialog", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("RegisterDialogUi", "back", Q_NULLPTR));
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
