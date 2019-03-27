/********************************************************************************
** Form generated from reading UI file 'gamedialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GAMEDIALOG_UI_H
#define GAMEDIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameDialog
{
public:
    QLCDNumber *countdownLcdNumber;
    QProgressBar *countdownProgressBar;
    QTextBrowser *wordTextBrowser;
    QTextBrowser *cardTextBrowser;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *backPushBotton;
    QPushButton *nextPushButton;
    QLineEdit *wordLineEdit;

    void setupUi(QDialog *GameDialog)
    {
        if (GameDialog->objectName().isEmpty())
            GameDialog->setObjectName(QStringLiteral("GameDialog"));
        GameDialog->resize(400, 300);
        countdownLcdNumber = new QLCDNumber(GameDialog);
        countdownLcdNumber->setObjectName(QStringLiteral("countdownLcdNumber"));
        countdownLcdNumber->setGeometry(QRect(280, 0, 64, 23));
        countdownProgressBar = new QProgressBar(GameDialog);
        countdownProgressBar->setObjectName(QStringLiteral("countdownProgressBar"));
        countdownProgressBar->setGeometry(QRect(20, 0, 251, 23));
        countdownProgressBar->setValue(24);
        wordTextBrowser = new QTextBrowser(GameDialog);
        wordTextBrowser->setObjectName(QStringLiteral("wordTextBrowser"));
        wordTextBrowser->setGeometry(QRect(50, 60, 251, 61));
        cardTextBrowser = new QTextBrowser(GameDialog);
        cardTextBrowser->setObjectName(QStringLiteral("cardTextBrowser"));
        cardTextBrowser->setGeometry(QRect(305, 221, 161, 141));
        horizontalLayoutWidget = new QWidget(GameDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 200, 166, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushBotton = new QPushButton(horizontalLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));

        horizontalLayout->addWidget(backPushBotton);

        nextPushButton = new QPushButton(horizontalLayoutWidget);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));

        horizontalLayout->addWidget(nextPushButton);

        wordLineEdit = new QLineEdit(GameDialog);
        wordLineEdit->setObjectName(QStringLiteral("wordLineEdit"));
        wordLineEdit->setGeometry(QRect(90, 140, 113, 20));

        retranslateUi(GameDialog);

        QMetaObject::connectSlotsByName(GameDialog);
    } // setupUi

    void retranslateUi(QDialog *GameDialog)
    {
        GameDialog->setWindowTitle(QApplication::translate("GameDialog", "Dialog", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("GameDialog", "PushButton", Q_NULLPTR));
        nextPushButton->setText(QApplication::translate("GameDialog", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameDialog: public Ui_GameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GAMEDIALOG_UI_H
