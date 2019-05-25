/********************************************************************************
** Form generated from reading UI file 'multiplayerMatchdialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MULTIPLAYERMATCHDIALOG_UI_H
#define MULTIPLAYERMATCHDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <qtmaterialraisedbutton.h>
#include "data/user.h"
#include "data/word.h"

QT_BEGIN_NAMESPACE

class Ui_MultiPlayerMatchDialog
{
public:
    QTableView *tableView;
    QtMaterialRaisedButton *backPushButton;

    void setupUi(QDialog *MultiPlayerMatchDialog)
    {
        if (MultiPlayerMatchDialog->objectName().isEmpty())
            MultiPlayerMatchDialog->setObjectName(QStringLiteral("MultiPlayerMatchDialog"));
        MultiPlayerMatchDialog->resize(564, 445);
        tableView = new QTableView(MultiPlayerMatchDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(80, 30, 401, 331));
        backPushButton = new QtMaterialRaisedButton(MultiPlayerMatchDialog);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setGeometry(QRect(106, 380, 351, 40));
        backPushButton->setMinimumSize(QSize(40, 40));

        retranslateUi(MultiPlayerMatchDialog);

        QMetaObject::connectSlotsByName(MultiPlayerMatchDialog);
    } // setupUi

    void retranslateUi(QDialog *MultiPlayerMatchDialog)
    {
        MultiPlayerMatchDialog->setWindowTitle(QApplication::translate("MultiPlayerMatchDialog", "Dialog", Q_NULLPTR));
        backPushButton->setText(QApplication::translate("MultiPlayerMatchDialog", "back", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MultiPlayerMatchDialog: public Ui_MultiPlayerMatchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MULTIPLAYERMATCHDIALOG_UI_H
