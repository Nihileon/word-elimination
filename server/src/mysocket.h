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

/**
 * @brief 断开socket
 *
 * @param handle
 */
    void disconnectSocket(qintptr handle) {
        if (handle == _handle) {
            disconnectFromHost();
        }
    }

/**
 * @brief Set the User Name object
 *
 * @param name
 */
    void setUserName(std::string name) { this->username = name; }
    std::string getUserName() { return username;
    }
private:
    std::string username; /// socket对应的用户名
    qintptr _handle; /// socket的描述符
signals:
/**
 * @brief 给服务器发送的断开信号
 *
 */
    void clientDisconnected(qintptr);

    /**
     * @brief 给服务器发送的连接信号
     *
     */
    void clientReadyRead(qintptr);
};

#endif // MYSOCKET_H
