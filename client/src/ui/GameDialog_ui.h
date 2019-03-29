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

class Ui_GameDialogUi
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

    void setupUi(QDialog *GameDialogUi)
    {
        if (GameDialogUi->objectName().isEmpty())
            GameDialogUi->setObjectName(QStringLiteral("GameDialogUi"));
        GameDialogUi->resize(400, 300);
        countdownLcdNumber = new QLCDNumber(GameDialogUi);
        countdownLcdNumber->setObjectName(QStringLiteral("countdownLcdNumber"));
        countdownLcdNumber->setGeometry(QRect(280, 0, 64, 23));
        countdownProgressBar = new QProgressBar(GameDialogUi);
        countdownProgressBar->setObjectName(QStringLiteral("countdownProgressBar"));
        countdownProgressBar->setGeometry(QRect(20, 0, 251, 23));
        countdownProgressBar->setValue(24);
        wordTextBrowser = new QTextBrowser(GameDialogUi);
        wordTextBrowser->setObjectName(QStringLiteral("wordTextBrowser"));
        wordTextBrowser->setGeometry(QRect(50, 60, 251, 61));
        cardTextBrowser = new QTextBrowser(GameDialogUi);
        cardTextBrowser->setObjectName(QStringLiteral("cardTextBrowser"));
        cardTextBrowser->setGeometry(QRect(305, 221, 161, 141));
        horizontalLayoutWidget = new QWidget(GameDialogUi);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(60, 200, 186, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushBotton = new QPushButton(horizontalLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));

        horizontalLayout->addWidget(backPushBotton);

        nextPushButton = new QPushButton(horizontalLayoutWidget);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));

        horizontalLayout->addWidget(nextPushButton);

        wordLineEdit = new QLineEdit(GameDialogUi);
        wordLineEdit->setObjectName(QStringLiteral("wordLineEdit"));
        wordLineEdit->setGeometry(QRect(90, 140, 113, 20));

        retranslateUi(GameDialogUi);

        QMetaObject::connectSlotsByName(GameDialogUi);
    } // setupUi

    void retranslateUi(QDialog *GameDialogUi)
    {
        GameDialogUi->setWindowTitle(QApplication::translate("GameDialogUi", "Dialog", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("GameDialogUi", "back", Q_NULLPTR));
        nextPushButton->setText(QApplication::translate("GameDialogUi", "next", Q_NULLPTR));
        wordLineEdit->setText(QApplication::translate("GameDialogUi", "123123", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GameDialogUi: public Ui_GameDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GAMEDIALOG_UI_H
