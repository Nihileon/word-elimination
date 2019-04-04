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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <qtmaterialraisedbutton.h>
#include <qtmaterialtextfield.h>
#include <ui/radiusprogressbar.h>

QT_BEGIN_NAMESPACE

class Ui_GameDialogUi
{
public:
    QLCDNumber *countdownLcdNumber;
    RadiusProgressBar *countdownProgressBar;
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
        GameDialogUi->resize(600, 500);
        countdownLcdNumber = new QLCDNumber(GameDialogUi);
        countdownLcdNumber->setObjectName(QStringLiteral("countdownLcdNumber"));
        countdownLcdNumber->setGeometry(QRect(260, 110, 151, 41));
        countdownProgressBar = new RadiusProgressBar(GameDialogUi);
        countdownProgressBar->setObjectName(QStringLiteral("countdownProgressBar"));
        countdownProgressBar->setGeometry(QRect(200, 150, 201, 41));
        countdownProgressBar->setValue(24);
        wordTextBrowser = new QTextBrowser(GameDialogUi);
        wordTextBrowser->setObjectName(QStringLiteral("wordTextBrowser"));
        wordTextBrowser->setGeometry(QRect(140, 200, 331, 61));
        cardTextBrowser = new QTextBrowser(GameDialogUi);
        cardTextBrowser->setObjectName(QStringLiteral("cardTextBrowser"));
        cardTextBrowser->setGeometry(QRect(90, 30, 421, 71));
        horizontalLayoutWidget = new QWidget(GameDialogUi);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(130, 380, 351, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        backPushBotton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        backPushBotton->setObjectName(QStringLiteral("backPushBotton"));
        backPushBotton->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(backPushBotton);

        nextPushButton = new QtMaterialRaisedButton(horizontalLayoutWidget);
        nextPushButton->setObjectName(QStringLiteral("nextPushButton"));
        nextPushButton->setMinimumSize(QSize(40, 40));

        horizontalLayout->addWidget(nextPushButton);

        wordLineEdit = new QtMaterialTextField(GameDialogUi);
        wordLineEdit->setObjectName(QStringLiteral("wordLineEdit"));
        wordLineEdit->setGeometry(QRect(130, 280, 351, 71));

        retranslateUi(GameDialogUi);

        QMetaObject::connectSlotsByName(GameDialogUi);
    } // setupUi

    void retranslateUi(QDialog *GameDialogUi)
    {
        GameDialogUi->setWindowTitle(QApplication::translate("GameDialogUi", "Dialog", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("GameDialogUi", "back", Q_NULLPTR));
        nextPushButton->setText(QApplication::translate("GameDialogUi", "next", Q_NULLPTR));
        wordLineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameDialogUi: public Ui_GameDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GAMEDIALOG_UI_H
