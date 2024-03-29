/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_UI_H
#define MAINWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *personalInfoTableView;
    QtMaterialRaisedButton *gamePushButton;
    QtMaterialRaisedButton *leaderboardPushBotton;
    QtMaterialRaisedButton *logoutPushBotton;
    QtMaterialRaisedButton *buildWordPushButton;
    QtMaterialRaisedButton *searchPushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QtMaterialRadioButton *singleModeRadioButton;
    QtMaterialRadioButton *doubleModeRadioButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(616, 404);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        personalInfoTableView = new QTableView(centralwidget);
        personalInfoTableView->setObjectName(QStringLiteral("personalInfoTableView"));
        personalInfoTableView->setGeometry(QRect(50, 110, 301, 241));
        personalInfoTableView->setStyleSheet(QLatin1String("border: none;background:white;\n"
"QTableCornerButton::section{border: none;background:white;}\n"
"QHeaderView{ border: none; background:white; }"));
        personalInfoTableView->setFrameShape(QFrame::NoFrame);
        personalInfoTableView->setFrameShadow(QFrame::Plain);
        personalInfoTableView->setLineWidth(0);
        personalInfoTableView->setShowGrid(false);
        personalInfoTableView->setGridStyle(Qt::DotLine);
        gamePushButton = new QtMaterialRaisedButton(centralwidget);
        gamePushButton->setObjectName(QStringLiteral("gamePushButton"));
        gamePushButton->setGeometry(QRect(370, 80, 191, 40));
        leaderboardPushBotton = new QtMaterialRaisedButton(centralwidget);
        leaderboardPushBotton->setObjectName(QStringLiteral("leaderboardPushBotton"));
        leaderboardPushBotton->setGeometry(QRect(370, 220, 191, 40));
        leaderboardPushBotton->setCheckable(false);
        leaderboardPushBotton->setFlat(false);
        logoutPushBotton = new QtMaterialRaisedButton(centralwidget);
        logoutPushBotton->setObjectName(QStringLiteral("logoutPushBotton"));
        logoutPushBotton->setGeometry(QRect(370, 290, 191, 40));
        buildWordPushButton = new QtMaterialRaisedButton(centralwidget);
        buildWordPushButton->setObjectName(QStringLiteral("buildWordPushButton"));
        buildWordPushButton->setGeometry(QRect(370, 80, 191, 40));
        searchPushButton = new QtMaterialRaisedButton(centralwidget);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));
        searchPushButton->setGeometry(QRect(370, 150, 191, 40));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 60, 291, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        singleModeRadioButton = new QtMaterialRadioButton(layoutWidget);
        singleModeRadioButton->setObjectName(QStringLiteral("singleModeRadioButton"));

        horizontalLayout->addWidget(singleModeRadioButton);

        doubleModeRadioButton = new QtMaterialRadioButton(layoutWidget);
        doubleModeRadioButton->setObjectName(QStringLiteral("doubleModeRadioButton"));

        horizontalLayout->addWidget(doubleModeRadioButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 616, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        gamePushButton->setText(QApplication::translate("MainWindow", "enter game", Q_NULLPTR));
        leaderboardPushBotton->setText(QApplication::translate("MainWindow", "leaderboard", Q_NULLPTR));
        logoutPushBotton->setText(QApplication::translate("MainWindow", "logout", Q_NULLPTR));
        buildWordPushButton->setText(QApplication::translate("MainWindow", "build new word", Q_NULLPTR));
        searchPushButton->setText(QApplication::translate("MainWindow", "search", Q_NULLPTR));
        singleModeRadioButton->setText(QApplication::translate("MainWindow", "single mode", Q_NULLPTR));
        doubleModeRadioButton->setText(QApplication::translate("MainWindow", "double mode", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_UI_H
