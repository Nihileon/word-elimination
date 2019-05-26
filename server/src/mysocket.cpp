#include "mysocket.h"

MySocket::MySocket(qintptr handle, QObject *parent)
    : QTcpSocket(parent), _handle(handle) {
    this->setSocketDescriptor(_handle);
    connect(this, &MySocket::disconnected, [&]() {
        this->deleteLater();
        emit this->clientDisconnected(_handle);
    });
    connect(this, &MySocket::readyRead,
            [&]() { emit this->clientReadyRead(_handle); });
}

void MySocket::disconnectSocket(qintptr handle) {
    if (handle == _handle) {
        disconnectFromHost();
    }
}

void MySocket::setUserName(std::string name) { this->username = name; }

std::string MySocket::getUserName() { return username; }
