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
#include <set>
#include <thread>
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
    explicit MyTcpServer(QObject *parent = 0);
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
    virtual void incomingConnection(qintptr handle);
    ~MyTcpServer();
    /**
     * @brief 刷新匹配表, 发送给所有正在匹配的用户
     *
     */
    void renewOnlineTable();

    /**
     * @brief 发送对战请求
     *
     * @param senderHandle  发送者的handle
     * @param receiverName 接收者的用户名
     */
    void sendCompeteQuery(qintptr senderHandle, QString receiverName);
    /**
     * @brief 阻塞并延迟
     *
     * @param msec
     */
    void delayMsec(int msec);

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
    void addChallengerSlot(qintptr handle, QString username);

    /**
     * @brief 删除一个在线的挑战者 并更新表格
     *
     * @param handle
     */
    void deleteChallengerSlot(qintptr handle);

    /**
     * @brief 客户端断开
     *
     * @param handle
     */
    void clientDisconnectedSlot(qintptr handle);

    /**
     * @brief 从受到消息的socket中读取信息
     *
     * @param handle
     */
    void readMessage(qintptr handle);

    /**
     * @brief 发送消息给对应的socket
     *
     * @param socket 需要发送的socket
     * @param data
     */
    void sendMessage(MySocket *socket, QString &data);

private:
    QMap<qintptr, MySocket *> clients;    /// 所有客户端
    QMap<qintptr, QString> users;         /// 正在匹配状态的用户
    QMap<qintptr, qintptr> currentOnline; /// 正在对战的用户对
};

#endif // MYTCPSERVER_H
