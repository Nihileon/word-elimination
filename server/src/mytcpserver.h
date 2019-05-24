#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include "data/transformation.h"
#include "data/user.h"
#include "data/word.h"
#include "mysocket.h"
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <mutex>
#include <thread>

class MyTcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0) : QTcpServer(parent) {
        // whenever a user connects, it will emit signal
        connect(this, &MyTcpServer::renewOnlineTable, this,
                &MyTcpServer::renewOnlineTableSlot);
    }
    static void destroy();
    void parseAndReply(MySocket *socket, QString &);
    virtual void incomingConnection(qintptr handle) {
        if (clients.size() > maxPendingConnections()) {
            QTcpSocket tcp;
            tcp.setSocketDescriptor(handle);
            tcp.disconnectFromHost();
            return;
        }
        auto clientSocket = new MySocket(handle);
        Q_ASSERT(clientSocket->socketDescriptor() == handle);

        connect(clientSocket, &MySocket::clientDisconnected, this,
                &MyTcpServer ::clientDisconnectedSlot);
        connect(this, &MyTcpServer::initDisconnectClient, clientSocket,
                &MySocket::disconnectSocket);
        connect(clientSocket, &MySocket::clientReadyRead,this,
                &MyTcpServer::readMessage);

        clients.insert(handle, clientSocket);
        qDebug() << handle << "connected";
        emit clientConnected(handle, clientSocket);
    }
    ~MyTcpServer() {
        for (auto client : clients.values()) {
            client->disconnectFromHost();
            auto handle = client->socketDescriptor();
            client->deleteLater();
            emit clientDisconnected(handle);
        }
        this->close();
    }
signals:
    void clientConnected(qintptr, QTcpSocket *);
    void clientDisconnected(qintptr);
    void initDisconnectClient(qintptr);
    void renewOnlineTable();

public slots:

    void addClientSlot(qintptr handle, QString username) {
        users.insert(handle, username);
    }

    void clientDisconnectedSlot(qintptr handle) {
        clients.remove(handle);
        users.remove(handle);
        qDebug() << handle << "disconnected";
        emit renewOnlineTable();
        emit clientDisconnected(handle);
    }

    void renewOnlineTableSlot() {
        // add all online challengers to a table, and send it to all online
        // challengers
    }
    void readMessage(qintptr handle) {
        auto socket = clients.value(handle);
        qDebug() << "got readsignal" << socket->bytesAvailable() << "bytes";
        QString messsage = socket->readLine();
        parseAndReply(socket ,messsage);
    }
    void sendMessage(MySocket *socket, QString &data) {
        socket->write(data.toStdString().c_str());
        socket->flush();
        socket->waitForBytesWritten();
    }

private:

    QMap<qintptr, MySocket *> clients;
    QMap<qintptr, QString> users;
};

#endif // MYTCPSERVER_H
