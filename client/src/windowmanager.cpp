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
    gw->hide();
    QObject::connect(l,&LoginDialog::toReg, r, &RegisterDialog::show);
    QObject::connect(r, &RegisterDialog::toLogin, l, &LoginDialog::show);
    QObject::connect(l, &LoginDialog::toMain, gw, &MainWindow::show);
}
