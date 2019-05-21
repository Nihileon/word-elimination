#include "tcpclient.h"

TCPClient* TCPClient::_instance = nullptr;

TCPClient &TCPClient::instance(){
    if(_instance == nullptr){
        _instance = new TCPClient();
    }
    return *_instance;
}

void TCPClient::destroy(){
    if(_instance != nullptr){
        delete _instance;
    }
    return;
}
