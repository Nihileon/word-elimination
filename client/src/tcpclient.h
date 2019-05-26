#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "data/basicInfo.h"
#include "data/transformation.h"
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QTcpSocket>

class TCPClient : public QObject {
    Q_OBJECT
private:
    static TCPClient *_instance;
    QTcpSocket *socket;

    TCPClient() : socket(new QTcpSocket) { connectServer(); }
    void connectServer();

public:
    static TCPClient &instance();
    static void destroy();
    /**
     * @brief 连接服务器
     *
     */

    ~TCPClient();
    /**
     * @brief 用于发送消息给服务器
     *
     * @param message 消息字符串
     */
    void sendMessage(std::string message);

    /**
     * @brief 在发送请求后接受对应的信息, 并返回一个数组
     *
     * @return QVector<QVector<QString>>
     */
    QVector<QVector<QString>> readMessage();

    /**
     * @brief 如果在多人匹配模式下, 则利用信号与槽接受信息,
     * 并根据不同的信息来进行不同的操作
     * 如果接收到的是匹配表则发送更新匹配表信号,
     * 如果接收到对方的对战请求则给匹配窗口发送匹配请求信号
     * 如果接收到游戏开始, 则直接进入游戏
     * 如果接受到游戏结束, 则直接跳回主窗口
     */
    void readMultiPlayerMessage();

    /**
     * @brief 发送匹配请求, 接受匹配表
     *
     * @param qv 自己的信息
     */
    void sendBeginMatchingRequest(QVariant info);

    /**
     * @brief 发送结束匹配请求
     *
     * @param qv 自己的信息
     */
    void sendEndMatchingRequest(QVariant info);

    /**
     * @brief 发送拒绝对战信息
     *
     * @param table 自己和对方的信息
     */
    void sendRefuseCompeteQuery(QString table);

    /**
     * @brief 发送同意对战的信息
     *
     * @param table 自己和对方的信息
     */
    void sendAgreeCompeteQuery(QString table);

    /**
     * @brief 结束游戏, 断开自动接受信息的信号与槽
     *
     */
    void gameEnd();

signals:
    /**
     * @brief 给匹配窗口发送匹配表
     *
     * @param table
     */
    void sendMultiPlayerTable(QVector<QVector<QString>> table);
    /**
     * @brief 给匹配窗口发送的对战请求, 让用户决定是否对战
     *
     * @param table
     */
    void sendCompeteRequest(QVector<QVector<QString>> table);
    /**
     * @brief 开始游戏, 将单词发送给对战界面
     *
     * @param table
     */
    void beginMultiPlayerGame(QVector<QVector<QString>> table);
    /**
     * @brief 从对战窗口返回主界面的信号
     *
     */
    void toMain();
};

#endif // TCPCLIENT_H
