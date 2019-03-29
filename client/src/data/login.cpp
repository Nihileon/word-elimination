#include "login.h"
Login* Login::_instance = nullptr;

Login& Login::instance(){
    if(_instance == nullptr){
        _instance = new Login();
    }
    return *_instance;
}

void Login::destroy(){
    delete _instance;
}
