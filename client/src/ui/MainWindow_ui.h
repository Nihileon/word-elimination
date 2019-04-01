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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <qtmaterialflatbutton.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *personalInfoTableView;
    QtMaterialFlatButton *gamePushButton;
    QtMaterialFlatButton *leaderboardPushBotton;
    QtMaterialFlatButton *logoutPushBotton;
    QtMaterialFlatButton *buildWordPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        personalInfoTableView = new QTableView(centralwidget);
        personalInfoTableView->setObjectName(QStringLiteral("personalInfoTableView"));
        personalInfoTableView->setGeometry(QRect(30, 60, 281, 431));
        personalInfoTableView->setFrameShadow(QFrame::Plain);
        personalInfoTableView->setGridStyle(Qt::DotLine);
        gamePushButton = new QtMaterialFlatButton(centralwidget);
        gamePushButton->setObjectName(QStringLiteral("gamePushButton"));
        gamePushButton->setGeometry(QRect(410, 140, 220, 40));
        leaderboardPushBotton = new QtMaterialFlatButton(centralwidget);
        leaderboardPushBotton->setObjectName(QStringLiteral("leaderboardPushBotton"));
        leaderboardPushBotton->setGeometry(QRect(410, 230, 220, 40));
        leaderboardPushBotton->setCheckable(false);
        leaderboardPushBotton->setFlat(false);
        logoutPushBotton = new QtMaterialFlatButton(centralwidget);
        logoutPushBotton->setObjectName(QStringLiteral("logoutPushBotton"));
        logoutPushBotton->setGeometry(QRect(410, 320, 220, 40));
        buildWordPushButton = new QtMaterialFlatButton(centralwidget);
        buildWordPushButton->setObjectName(QStringLiteral("buildWordPushButton"));
        buildWordPushButton->setGeometry(QRect(410, 140, 220, 40));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_UI_H
