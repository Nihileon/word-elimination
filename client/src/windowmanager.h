/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:17:09
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:17:09
 */
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "tcpclient.h"
#include "widgets/BuildWordDialog.h"
#include "widgets/GameDialog.h"
#include "widgets/LeaderBoardDialog.h"
#include "widgets/LoginDialog.h"
#include "widgets/MainWindow.h"
#include "widgets/RegisterDialog.h"
#include "widgets/SearchDialog.h"
#include "widgets/doubleplayerdialog.h"
#include "widgets/multiplayermatchdialog.h"
#include <QApplication>
#include <QObject>
/**
 * @brief 窗口管理者类, 对所有窗口的交互进行管理
 *
 */
class Manager {
private:
    static Manager *_instance;
    Manager()
        : mw(new MainWindow), l(new LoginDialog), r(new RegisterDialog),
          g(new GameDialog), b(new BuildWordDialog), lb(new LeaderboardDialog),
          s(new SearchDialog), d(new DoublePlayerDialog),
          mm(new MultiPlayerMatchDialog) {}

public:
    MainWindow *mw;
    LoginDialog *l;
    RegisterDialog *r;
    GameDialog *g;
    BuildWordDialog *b;
    LeaderboardDialog *lb;
    SearchDialog *s;
    DoublePlayerDialog *d;
    MultiPlayerMatchDialog *mm;
    ~Manager() {
        delete mw;
        delete l;
        delete r;
        delete g;
        delete b;
        delete lb;
        delete s;
        delete d;
        delete mm;
    }

    static Manager &instance();
    static void destroy();
    void init();
};

#endif // WINDOWMANAGER_H
