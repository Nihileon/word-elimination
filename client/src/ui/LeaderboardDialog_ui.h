/********************************************************************************
** Form generated from reading UI file 'leaderboarddialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef LEADERBOARDDIALOG_UI_H
#define LEADERBOARDDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_LeaderboardDialog
{
public:
    QTableView *leaderboardTableView;
    QComboBox *characterComboBox;
    QPushButton *backPushButton;

    void setupUi(QDialog *LeaderboardDialog)
    {
        if (LeaderboardDialog->objectName().isEmpty())
            LeaderboardDialog->setObjectName(QStringLiteral("LeaderboardDialog"));
        LeaderboardDialog->resize(400, 300);
        leaderboardTableView = new QTableView(LeaderboardDialog);
        leaderboardTableView->setObjectName(QStringLiteral("leaderboardTableView"));
        leaderboardTableView->setGeometry(QRect(40, 30, 311, 221));
        characterComboBox = new QComboBox(LeaderboardDialog);
        characterComboBox->setObjectName(QStringLiteral("characterComboBox"));
        characterComboBox->setGeometry(QRect(110, 10, 181, 22));
        backPushButton = new QPushButton(LeaderboardDialog);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setGeometry(QRect(70, 260, 80, 14));

        retranslateUi(LeaderboardDialog);

        QMetaObject::connectSlotsByName(LeaderboardDialog);
    } // setupUi

    void retranslateUi(QDialog *LeaderboardDialog)
    {
        LeaderboardDialog->setWindowTitle(QApplication::translate("LeaderboardDialog", "Dialog", Q_NULLPTR));
        characterComboBox->clear();
        characterComboBox->insertItems(0, QStringList()
         << QApplication::translate("LeaderboardDialog", "WordBuilder", Q_NULLPTR)
         << QApplication::translate("LeaderboardDialog", "Challenger", Q_NULLPTR)
        );
        backPushButton->setText(QApplication::translate("LeaderboardDialog", "back", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LeaderboardDialog: public Ui_LeaderboardDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LEADERBOARDDIALOG_UI_H