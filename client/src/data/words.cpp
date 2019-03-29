#include "word.h"
Word* Word::_instance = nullptr;

auto Word::instance(){
    if(_instance == nullptr){
        _instance = new Word();
    }
    return _instance;
}

void Word::destroy(){
    if(_instance != nullptr){
        delete _instance;
    }
    return;
}
