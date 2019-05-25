#ifndef MYSOCKET_H
#define MYSOCKET_H
#include <qtcpsocket.h>
#include <mutex>
#include "data/transformation.h"
#include "data/user.h"
#include "data/word.h"
class MySocket:public QTcpSocket
{
    Q_OBJECT
public:
    MySocket(qintptr handle, QObject *parent = 0)
        : QTcpSocket(parent), _handle(handle) {

        this->setSocketDescriptor(_handle);
        connect(this, &MySocket::disconnected, [&]() {
            this->deleteLater();
            emit this->clientDisconnected(_handle);
        });
        connect(this, &MySocket::readyRead,
                [&]() { emit this->clientReadyRead(_handle); });

    }


    void disconnectSocket(qintptr handle) {
        if (handle == _handle) {
            disconnectFromHost();
        }
    }

    void setUserName(std::string name) { this->username = name; }
    std::string getUserName() { return username;
    }
private:
    std::string username;
    qintptr _handle;
    QString userType = "";
signals:
    void clientDisconnected(qintptr);
    void clientReadyRead(qintptr);
};

#endif // MYSOCKET_H
