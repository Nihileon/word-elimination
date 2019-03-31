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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *personalInfoTableView;
    QPushButton *gamePushButton;
    QPushButton *leaderboardPushBotton;
    QPushButton *logoutPushBotton;
    QPushButton *buildWordPushButton;
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
        personalInfoTableView->setGeometry(QRect(30, 20, 281, 431));
        gamePushButton = new QPushButton(centralwidget);
        gamePushButton->setObjectName(QStringLiteral("gamePushButton"));
        gamePushButton->setGeometry(QRect(420, 90, 221, 41));
        leaderboardPushBotton = new QPushButton(centralwidget);
        leaderboardPushBotton->setObjectName(QStringLiteral("leaderboardPushBotton"));
        leaderboardPushBotton->setGeometry(QRect(420, 230, 211, 41));
        logoutPushBotton = new QPushButton(centralwidget);
        logoutPushBotton->setObjectName(QStringLiteral("logoutPushBotton"));
        logoutPushBotton->setGeometry(QRect(420, 340, 191, 41));
        buildWordPushButton = new QPushButton(centralwidget);
        buildWordPushButton->setObjectName(QStringLiteral("buildWordPushButton"));
        buildWordPushButton->setGeometry(QRect(420, 70, 221, 41));
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
