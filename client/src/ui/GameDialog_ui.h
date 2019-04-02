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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>

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
    QtMaterialRaisedButton *backPushBotton;
    QtMaterialRaisedButton *nextPushButton;
    QtMaterialTextField *wordLineEdit;

    void setupUi(QDialog *GameDialogUi)
    {
        if (GameDialogUi->objectName().isEmpty())
            GameDialogUi->setObjectName(QStringLiteral("GameDialogUi"));
        GameDialogUi->resize(688, 666);
        countdownLcdNumber = new QLCDNumber(GameDialogUi);
        countdownLcdNumber->setObjectName(QStringLiteral("countdownLcdNumber"));
        countdownLcdNumber->setGeometry(QRect(400, 22, 151, 41));
        countdownProgressBar = new QProgressBar(GameDialogUi);
        countdownProgressBar->setObjectName(QStringLiteral("countdownProgressBar"));
        countdownProgressBar->setGeometry(QRect(100, 10, 281, 61));
        countdownProgressBar->setValue(24);
        wordTextBrowser = new QTextBrowser(GameDialogUi);
        wordTextBrowser->setObjectName(QStringLiteral("wordTextBrowser"));
        wordTextBrowser->setGeometry(QRect(50, 140, 571, 111));
        cardTextBrowser = new QTextBrowser(GameDialogUi);
        cardTextBrowser->setObjectName(QStringLiteral("cardTextBrowser"));
        cardTextBrowser->setGeometry(QRect(470, 450, 161, 141));
        horizontalLayoutWidget = new QWidget(GameDialogUi);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(130, 470, 186, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushBotton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));

        horizontalLayout->addWidget(backPushBotton);

        nextPushButton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));

        horizontalLayout->addWidget(nextPushButton);

        wordLineEdit = new QtMaterialTextField(GameDialogUi);
        wordLineEdit->setObjectName(QStringLiteral("wordLineEdit"));
        wordLineEdit->setGeometry(QRect(110, 320, 351, 71));

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
