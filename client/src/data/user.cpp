#include "user.h"
User* User::_instance = nullptr;

User& User::instance(){
    if(_instance == nullptr){
        _instance = new User();
    }
    return *_instance;
}

void User::destroy(){
    if(_instance != nullptr){
        delete _instance;
    }
    return;
}
