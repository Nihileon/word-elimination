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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>

QT_BEGIN_NAMESPACE

class Ui_LeaderboardDialogUi
{
public:
    QTableView *leaderboardTableView;
    QtMaterialRaisedButton *backPushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QtMaterialRadioButton *challengerRadioButton;
    QtMaterialRadioButton *wordRadioButton;

    void setupUi(QDialog *LeaderboardDialogUi)
    {
        if (LeaderboardDialogUi->objectName().isEmpty())
            LeaderboardDialogUi->setObjectName(QStringLiteral("LeaderboardDialogUi"));
        LeaderboardDialogUi->resize(733, 576);
        leaderboardTableView = new QTableView(LeaderboardDialogUi);
        leaderboardTableView->setObjectName(QStringLiteral("leaderboardTableView"));
        leaderboardTableView->setGeometry(QRect(70, 70, 591, 421));
        leaderboardTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        leaderboardTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        backPushButton = new QtMaterialRaisedButton(LeaderboardDialogUi);
        backPushButton->setObjectName(QStringLiteral("backPushButton"));
        backPushButton->setGeometry(QRect(170, 510, 391, 41));
        layoutWidget = new QWidget(LeaderboardDialogUi);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(200, 10, 309, 56));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        challengerRadioButton = new QtMaterialRadioButton(layoutWidget);
        challengerRadioButton->setObjectName(QStringLiteral("challengerRadioButton"));

        horizontalLayout->addWidget(challengerRadioButton);

        wordRadioButton = new QtMaterialRadioButton(layoutWidget);
        wordRadioButton->setObjectName(QStringLiteral("wordRadioButton"));

        horizontalLayout->addWidget(wordRadioButton);


        retranslateUi(LeaderboardDialogUi);

        QMetaObject::connectSlotsByName(LeaderboardDialogUi);
    } // setupUi

    void retranslateUi(QDialog *LeaderboardDialogUi)
    {
        LeaderboardDialogUi->setWindowTitle(QApplication::translate("LeaderboardDialogUi", "Dialog", Q_NULLPTR));
        backPushButton->setText(QApplication::translate("LeaderboardDialogUi", "back", Q_NULLPTR));
        challengerRadioButton->setText(QApplication::translate("LeaderboardDialogUi", "challenger", Q_NULLPTR));
        wordRadioButton->setText(QApplication::translate("LeaderboardDialogUi", "word builder", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LeaderboardDialogUi: public Ui_LeaderboardDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // LEADERBOARDDIALOG_UI_H
