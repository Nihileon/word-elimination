#include "windowmanager.h"

Manager* Manager::_instance = nullptr;
Manager& Manager::instance(){
    if(_instance == nullptr){
        _instance = new Manager();
    }
    return *_instance;
}

void Manager::destroy(){
    delete _instance;
}

void Manager::init(){
    l->show();
    r->hide();
    mw->hide();
    QObject::connect(l,&LoginDialog::toReg, r, &RegisterDialog::show);
    QObject::connect(l, &LoginDialog::toMain, mw, &MainWindow::show);
    QObject::connect(l,&LoginDialog::sendUser, mw, &MainWindow::setUser);
    QObject::connect(r, &RegisterDialog::toLogin, l, &LoginDialog::show);
    QObject::connect(r, &RegisterDialog::sendUser, mw, &MainWindow::setUser);
    QObject::connect(r, &RegisterDialog::toMainWindow, mw, &MainWindow::show);
    QObject::connect(mw,&MainWindow::toGame, g, &GameDialog::gameBegin);
    QObject::connect(mw, &MainWindow::sendChallenger, g, &GameDialog::setChallenger);
    QObject::connect(mw, &MainWindow::sendWordBuilder, b, &BuildWordDialog::setWordBuilder);
    QObject::connect(mw, &MainWindow::toBuildWord, b, &BuildWordDialog::show);
    QObject::connect(mw, &MainWindow::toLeader, lb,&LeaderboardDialog::showThis);
    QObject::connect(g, &GameDialog::toMain, mw, &MainWindow::show);
    QObject::connect(g,&GameDialog::sendChallenger,mw, &MainWindow::setChallenger);
    QObject::connect(b, &BuildWordDialog::sendWordBuilder, mw, &MainWindow::setWordBuilder);
    QObject::connect(b, &BuildWordDialog::toMain, mw, &MainWindow::show);
    QObject::connect(lb, &LeaderboardDialog::toMain, mw, &MainWindow::show);
}
