/********************************************************************************
** Form generated from reading UI file 'buildworddialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BUILDWORDDIALOG_UI_H
#define BUILDWORDDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuildWordDialogUi
{
public:
    QLineEdit *newWordLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backPushButton;
    QPushButton *confirmPushBotton;

    void setupUi(QDialog *BuildWordDialogUi)
    {
        if (BuildWordDialogUi->objectName().isEmpty())
            BuildWordDialogUi->setObjectName(QStringLiteral("BuildWordDialogUi"));
        BuildWordDialogUi->resize(567, 439);
        newWordLineEdit = new QLineEdit(BuildWordDialogUi);
        newWordLineEdit->setObjectName(QStringLiteral("newWordLineEdit"));
        newWordLineEdit->setGeometry(QRect(160, 130, 211, 61));
        horizontalLayoutWidget = new QWidget(BuildWordDialogUi);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(150, 220, 261, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushButton = new QPushButton(horizontalLayoutWidget);
        backPushButton->setObjectName(QStringLiteral("bakcPushButton"));

        horizontalLayout->addWidget(backPushButton);

        confirmPushBotton = new QPushButton(horizontalLayoutWidget);
        confirmPushBotton->setObjectName(QStringLiteral("confirmPushBotton"));

        horizontalLayout->addWidget(confirmPushBotton);


        retranslateUi(BuildWordDialogUi);

        QMetaObject::connectSlotsByName(BuildWordDialogUi);
    } // setupUi

    void retranslateUi(QDialog *BuildWordDialogUi)
    {
        BuildWordDialogUi->setWindowTitle(QApplication::translate("BuildWordDialogUi", "Dialog", Q_NULLPTR));
        backPushButton->setText(QApplication::translate("BuildWordDialogUi", "back", Q_NULLPTR));
        confirmPushBotton->setText(QApplication::translate("BuildWordDialogUi", "make new word", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuildWordDialogUi: public Ui_BuildWordDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BUILDWORDDIALOG_UI_H
