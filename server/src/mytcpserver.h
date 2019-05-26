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
/**
 * @brief 正在对战的两个人
 *
 */
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


/**
 * @brief 服务器
 *
 */
class MyTcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0) : QTcpServer(parent) {
    }
    static void destroy();
    /**
     * @brief 解析接收到的信息, 并在将对应请求发送回发送方
     *
     * @param socket
     */
    void parseAndReply(MySocket *socket, QString &);

    /**
     * @brief 有来的信号就将其连接到服务器
     *
     * @param handle
     */
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
    /**
     * @brief 刷新匹配表, 发送给所有正在匹配的用户
     *
     */
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

    /**
     * @brief 发送对战请求
     *
     * @param senderHandle  发送者的handle
     * @param receiverName 接收者的用户名
     */
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
/**
 * @brief 阻塞并延迟
 *
 * @param msec
 */
    void delayMsec(int msec) {
        QTime _timer = QTime::currentTime();
        QTime _nowTimer;
        do {
            _nowTimer = QTime::currentTime();
        } while (_timer.msecsTo(_nowTimer) < msec);
    }

signals:
/**
 * @brief 让客户端断开的信号
 *
 */
    void clientDisconnected(qintptr);
    /**
     * @brief 在服务器上删除该客户端
     *
     */
    void initDisconnectClient(qintptr);

public slots:

    /**
     * @brief 添加在线的挑战者 并更新表格
     *
     * @param handle
     * @param username
     */
    void addChallengerSlot(qintptr handle, QString username) {
        qDebug() << "addChallengerSlot" <<username;
        users.insert(handle, username);
        renewOnlineTable();
    }

/**
 * @brief 删除一个在线的挑战者 并更新表格
 *
 * @param handle
 */
    void deleteChallengerSlot(qintptr handle) {
        qDebug() << "deleteChallengerSlot";
        users.remove(handle);
        renewOnlineTable();
    }

/**
 * @brief 客户端断开
 *
 * @param handle
 */
    void clientDisconnectedSlot(qintptr handle) {
        clients.remove(handle);
        users.remove(handle);
        qDebug() << handle << "disconnected";
        renewOnlineTable();
        emit clientDisconnected(handle);
    }

/**
 * @brief 从受到消息的socket中读取信息
 *
 * @param handle
 */
    void readMessage(qintptr handle) {
        auto socket = clients.value(handle);
        qDebug() << "got readsignal" << socket->bytesAvailable() << "bytes";
        QString messsage = socket->readLine();
        qDebug() << messsage;
        parseAndReply(socket, messsage);
    }

    /**
     * @brief 发送消息给对应的socket
     *
     * @param socket 需要发送的socket
     * @param data
     */
    void sendMessage(MySocket *socket, QString &data) {
        qDebug() << data;
        socket->write(data.toStdString().c_str());
        socket->flush();
        socket->waitForBytesWritten();
    }

private:
    QMap<qintptr, MySocket *> clients; /// 所有客户端
    QMap<qintptr, QString> users; /// 正在匹配状态的用户
    QMap<qintptr, qintptr> currentOnline; /// 正在对战的用户对
};

#endif // MYTCPSERVER_H
