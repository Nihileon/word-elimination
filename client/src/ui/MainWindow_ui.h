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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(532, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        personalInfoTableView = new QTableView(centralwidget);
        personalInfoTableView->setObjectName(QStringLiteral("personalInfoTableView"));
        personalInfoTableView->setGeometry(QRect(60, 120, 231, 221));
        personalInfoTableView->setFrameShape(QFrame::NoFrame);
        personalInfoTableView->setFrameShadow(QFrame::Plain);
        personalInfoTableView->setLineWidth(0);
        personalInfoTableView->setShowGrid(false);
        personalInfoTableView->setGridStyle(Qt::DotLine);
        gamePushButton = new QtMaterialRaisedButton(centralwidget);
        gamePushButton->setObjectName(QStringLiteral("gamePushButton"));
        gamePushButton->setGeometry(QRect(300, 70, 211, 40));
        leaderboardPushBotton = new QtMaterialRaisedButton(centralwidget);
        leaderboardPushBotton->setObjectName(QStringLiteral("leaderboardPushBotton"));
        leaderboardPushBotton->setGeometry(QRect(300, 170, 211, 40));
        leaderboardPushBotton->setCheckable(false);
        leaderboardPushBotton->setFlat(false);
        logoutPushBotton = new QtMaterialRaisedButton(centralwidget);
        logoutPushBotton->setObjectName(QStringLiteral("logoutPushBotton"));
        logoutPushBotton->setGeometry(QRect(300, 260, 211, 40));
        buildWordPushButton = new QtMaterialRaisedButton(centralwidget);
        buildWordPushButton->setObjectName(QStringLiteral("buildWordPushButton"));
        buildWordPushButton->setGeometry(QRect(300, 70, 211, 40));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 532, 28));
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
