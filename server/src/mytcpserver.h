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
#include <set>
struct competitorPair {
    QString competitorA, competitorB;
    qintptr handleA, handleB;
    competitorPair(QString cpA, qintptr hdA, QString cpB, qintptr hdB) {
        competitorA = cpA;
        handleA = hdA;
        competitorB = cpB;
        handleB = hdB;
    }
    friend bool operator<(const competitorPair &a, const competitorPair &b) {
        if (a.handleA < b.handleA)
            return true;
        return false;
    }
};



class MyTcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0) : QTcpServer(parent) {
        // whenever a user connects, it will emit signal
        //        connect(this, &MyTcpServer::renewOnlineTable, this,
        //                &MyTcpServer::renewOnlineTableSlot);
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
        connect(clientSocket, &MySocket::clientReadyRead, this,
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
    void renewOnlineTable() {
        qDebug() << "renewOnlineTable";
        QVector<QVector<QString>> table;
        QVector<QString> info;
        info.push_back("MULTIPLAYER_TABLE");
        table.push_back(info);
        for (auto value : users.values()) {
            QVector<QString> user;
            LoginInfo li;
            li.usr = value.toStdString();
            auto ci = User::instance().getChallenger(li);
            user.push_back(QString::fromStdString(ci.usr));
            user.push_back(QString::number(ci.level));
            table.push_back(user);
        }
        for (auto challengerHandle : users.keys()) {
            auto socket = clients.value(challengerHandle);
            auto data =
                QString::fromStdString(transformation::tableToString(table));
            sendMessage(socket, data);
        }
    }
    void sendCompeteQuery(qintptr senderHandle, QString receiverName) {
        qDebug() << "sendCompeteQuery";
        LoginInfo sender;
        sender.usr = users.value(senderHandle).toStdString();
        auto senderInfo = User::instance().getChallenger(sender);

        LoginInfo receiver;
        receiver.usr = receiverName.toStdString();
        auto receiverInfo = User::instance().getChallenger(receiver);
        auto receiverHandle = users.key(receiverName);


        users.remove(receiverHandle);
        users.remove(senderHandle);
        renewOnlineTable();

        QString data = "COMPETE_QUERY_TO_CLIENT|";
        // senderName+senderLevel+receiverName+ReceiverLevel
        data.append(QString::fromStdString(senderInfo.usr) + "," +
                    QString::number(senderInfo.level) +","+ QString::number(senderHandle)+ "|");

        data.append(QString::fromStdString(receiverInfo.usr) + "," +
                    QString::number(receiverInfo.level)+","+ QString::number(receiverHandle));
        sendMessage(clients.value(receiverHandle), data);
    }
    void delayMsec(int msec) {
        QTime _timer = QTime::currentTime();
        QTime _nowTimer;
        do {
            _nowTimer = QTime::currentTime();
        } while (_timer.msecsTo(_nowTimer) < msec);
    }
signals:
    void clientConnected(qintptr, QTcpSocket *);
    void clientDisconnected(qintptr);
    void initDisconnectClient(qintptr);

public slots:

    void addChallengerSlot(qintptr handle, QString username) {
        qDebug() << "addChallengerSlot" <<username;
        users.insert(handle, username);
        renewOnlineTable();
    }

    void deleteChallengerSlot(qintptr handle) {
        qDebug() << "deleteChallengerSlot";
        users.remove(handle);
        renewOnlineTable();
    }

    void clientDisconnectedSlot(qintptr handle) {
        clients.remove(handle);
        users.remove(handle);
        qDebug() << handle << "disconnected";
        renewOnlineTable();
        emit clientDisconnected(handle);
    }

    void readMessage(qintptr handle) {
        auto socket = clients.value(handle);
        qDebug() << "got readsignal" << socket->bytesAvailable() << "bytes";
        QString messsage = socket->readLine();
        qDebug() << messsage;
        parseAndReply(socket, messsage);
    }
    void sendMessage(MySocket *socket, QString &data) {
        qDebug() << data;
        socket->write(data.toStdString().c_str());
        socket->flush();
        socket->waitForBytesWritten();
    }

private:
    QMap<qintptr, MySocket *> clients;
    QMap<qintptr, QString> users;
//    std::set<competitorPair> currentCompetingPairs;
    QMap<qintptr, qintptr> currentOnline;
};

#endif // MYTCPSERVER_H
