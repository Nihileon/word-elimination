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
#include <QtWidgets/QWidget>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>

QT_BEGIN_NAMESPACE

/**
 * @brief 出题界面的ui
 *
 */
class Ui_BuildWordDialogUi
{
public:
    QtMaterialTextField *newWordLineEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QtMaterialRaisedButton *backPushButton;
    QtMaterialRaisedButton *confirmPushBotton;

    void setupUi(QDialog *BuildWordDialogUi)
    {
        if (BuildWordDialogUi->objectName().isEmpty())
            BuildWordDialogUi->setObjectName(QStringLiteral("BuildWordDialogUi"));
        BuildWordDialogUi->resize(500, 400);
        BuildWordDialogUi->setSizeGripEnabled(false);
        newWordLineEdit = new QtMaterialTextField(BuildWordDialogUi);
        newWordLineEdit->setObjectName(QStringLiteral("newWordLineEdit"));
        newWordLineEdit->setGeometry(QRect(120, 150, 261, 51));
        horizontalLayoutWidget = new QWidget(BuildWordDialogUi);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(90, 229, 321, 91));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushButton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setMinimumSize(QSize(40, 40));

        horizontalLayout->addWidget(backPushButton);

        confirmPushBotton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        confirmPushBotton->setObjectName(QStringLiteral("confirmPushBotton"));
        confirmPushBotton->setMinimumSize(QSize(0, 40));

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
