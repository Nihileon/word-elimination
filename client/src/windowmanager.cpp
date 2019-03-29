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
    QObject::connect(r, &RegisterDialog::toLogin, l, &LoginDialog::show);
    QObject::connect(l, &LoginDialog::toMain, mw, &MainWindow::show);
    QObject::connect(mw,&MainWindow::toGame, g, &GameDialog::show);
    QObject::connect(g, &GameDialog::toMain, mw, &MainWindow::show);

}
