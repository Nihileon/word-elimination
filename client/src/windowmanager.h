#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QApplication>
#include <QObject>
#include "widgets/LoginDialog.h"
#include "widgets/MainWindow.h"
#include "widgets/RegisterDialog.h"
#include "widgets/GameDialog.h"
#include "widgets/BuildWordDialog.h"
#include "widgets/LeaderBoardDialog.h"
#include "widgets/SearchDialog.h"

class Manager{
public:
    MainWindow* mw;
    LoginDialog* l;
    RegisterDialog* r;
    GameDialog* g;
    BuildWordDialog* b;
    LeaderboardDialog* lb;
    SearchDialog* s;
    static Manager *_instance;

    Manager():mw(new MainWindow),
        l(new LoginDialog),
        r(new RegisterDialog),
        g(new GameDialog),
        b(new BuildWordDialog),
        lb(new LeaderboardDialog),
        s(new SearchDialog){}

    ~Manager(){
        delete mw;
        delete l;
        delete r;
        delete g;
        delete b;
        delete lb;
        delete s;
    }

    static Manager& instance();
    static void destroy();
    void init();

};

#endif // WINDOWMANAGER_H
