/********************************************************************************
** Form generated from reading UI file 'doubleplayerdialog_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DOUBLEPLAYERDIALOG_UI_H
#define DOUBLEPLAYERDIALOG_UI_H

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

class Ui_DoublePlayerDialog
{
public:
    QLCDNumber *countdownLcdNumber;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QtMaterialRaisedButton *backPushBotton;
    QtMaterialRaisedButton *nextPushButton;
    RadiusProgressBar *countdownProgressBar;
    QtMaterialTextField *wordLineEdit;
    QTextBrowser *wordTextBrowser;

    void setupUi(QDialog *DoublePlayerDialog)
    {
        if (DoublePlayerDialog->objectName().isEmpty())
            DoublePlayerDialog->setObjectName(QStringLiteral("DoublePlayerDialog"));
        DoublePlayerDialog->resize(565, 445);
        countdownLcdNumber = new QLCDNumber(DoublePlayerDialog);
        countdownLcdNumber->setObjectName(QStringLiteral("countdownLcdNumber"));
        countdownLcdNumber->setGeometry(QRect(240, 40, 151, 41));
        horizontalLayoutWidget = new QWidget(DoublePlayerDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(110, 310, 351, 80));
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

        countdownProgressBar = new RadiusProgressBar(DoublePlayerDialog);
        countdownProgressBar->setObjectName(QStringLiteral("countdownProgressBar"));
        countdownProgressBar->setGeometry(QRect(180, 80, 201, 41));
        countdownProgressBar->setValue(24);
        wordLineEdit = new QtMaterialTextField(DoublePlayerDialog);
        wordLineEdit->setObjectName(QStringLiteral("wordLineEdit"));
        wordLineEdit->setGeometry(QRect(110, 210, 351, 71));
        wordTextBrowser = new QTextBrowser(DoublePlayerDialog);
        wordTextBrowser->setObjectName(QStringLiteral("wordTextBrowser"));
        wordTextBrowser->setGeometry(QRect(120, 130, 331, 61));

        retranslateUi(DoublePlayerDialog);

        QMetaObject::connectSlotsByName(DoublePlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *DoublePlayerDialog)
    {
        DoublePlayerDialog->setWindowTitle(QApplication::translate("DoublePlayerDialog", "Dialog", Q_NULLPTR));
        backPushBotton->setText(QApplication::translate("DoublePlayerDialog", "back", Q_NULLPTR));
        nextPushButton->setText(QApplication::translate("DoublePlayerDialog", "next", Q_NULLPTR));
        wordLineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DoublePlayerDialog: public Ui_DoublePlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DOUBLEPLAYERDIALOG_UI_H
