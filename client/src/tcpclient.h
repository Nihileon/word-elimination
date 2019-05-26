#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "data/basicInfo.h"
#include "data/transformation.h"
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QTcpSocket>

class TCPClient : public QObject
{
    Q_OBJECT
  private:
    static TCPClient *_instance;
    QTcpSocket *socket;

    TCPClient() : socket(new QTcpSocket) { connectServer(); }
    void connectServer()
    {
        quint16 port = 8899;
        socket->connectToHost("127.0.0.1", port);
        if (socket->waitForConnected(10000)) {
            qDebug() << "connected";
        } else {
            qDebug() << "not connect";
        }
    }

  public:
    static TCPClient &instance();
    static void destroy();
    /**
     * @brief 连接服务器
     *
     */

    ~TCPClient() { delete socket; }
    /**
     * @brief 用于发送消息给服务器
     *
     * @param message 消息字符串
     */
    void sendMessage(std::string message)
    {
        qDebug() << "send message";
        socket->write(message.c_str());
        socket->flush();
        socket->waitForBytesWritten();
    }

    /**
     * @brief 在发送请求后接受对应的信息, 并返回一个数组
     *
     * @return QVector<QVector<QString>>
     */
    QVector<QVector<QString>> readMessage()
    {
        QVector<QVector<QString>> table;
        if (socket->waitForReadyRead()) {
            QString result = socket->readLine();
            table = transformation::stringToTable(result.toStdString());
        } else {
            qDebug() << "received nothing";
        }
        return table;
    }

    /**
     * @brief 如果在多人匹配模式下, 则利用信号与槽接受信息,
     * 并根据不同的信息来进行不同的操作
     * 如果接收到的是匹配表则发送更新匹配表信号,
     * 如果接收到对方的对战请求则给匹配窗口发送匹配请求信号
     * 如果接收到游戏开始, 则直接进入游戏
     * 如果接受到游戏结束, 则直接跳回主窗口
     */
    void readMultiPlayerMessage()
    {
        qDebug() << "readMultiplayermessage";
        QVector<QVector<QString>> table;
        QString result = socket->readLine();
        table = transformation::stringToTable(result.toStdString());
        if (table.at(0).at(0) == "MULTIPLAYER_TABLE") {
            table.erase(table.begin());
            emit sendMultiPlayerTable(table);
        } else if (table.at(0).at(0) == "COMPETE_QUERY_TO_CLIENT") {
            qDebug() << "COMPETE_QUERY_TO_CLIENT";
            table.erase(table.begin());
            emit sendCompeteRequest(table);
        } else if (table.at(0).at(0) == "MULTIPALYER_GAME_BEGIN") {
            qDebug() << "MULTIPALYER_GAME_BEGIN";
            table.erase(table.begin());
            emit beginMultiPlayerGame(table);
        } else if (table.at(0).at(0) == "DOUBLE_GAME_END") {
            emit toMain();
            disconnect(socket, &QTcpSocket::readyRead, this,
                       &TCPClient::readMultiPlayerMessage);
        }
    }

    /**
     * @brief 发送匹配请求, 接受匹配表
     *
     * @param qv 自己的信息
     */
    void sendBeginMatchingRequest(QVariant info)
    {
        qDebug() << "send begin matching request";
        connect(socket, &QTcpSocket::readyRead, this,
                &TCPClient::readMultiPlayerMessage);
        auto challenger = info.value<Challenger>();
        std::string qs = "MULTIPLAYER_QUERY|";
        qs.append(challenger.usr);
        sendMessage(qs.c_str());
    }

    /**
     * @brief 发送结束匹配请求
     *
     * @param qv 自己的信息
     */
    void sendEndMatchingRequest(QVariant info)
    {
        disconnect(socket, &QTcpSocket::readyRead, this,
                   &TCPClient::readMultiPlayerMessage);
        auto challenger = info.value<Challenger>();

        std::string qs = "END_MULTIPLAYER_QUERY|";
        qs.append(challenger.usr);
        sendMessage(qs.c_str());
    }

    /**
     * @brief 发送拒绝对战信息
     *
     * @param table 自己和对方的信息
     */
    void sendRefuseCompeteQuery(QString table)
    {
        qDebug() << "sendRefuseCompeteQuery";
        std::string data = "REFUSE_COMPETE_QUERY|";
        data.append(table.toStdString());
        sendMessage(data);
    }

    /**
     * @brief 发送同意对战的信息
     *
     * @param table 自己和对方的信息
     */
    void sendAgreeCompeteQuery(QString table)
    {
        qDebug() << "sendAgreeCompeteQuery";
        std::string data = "AGREE_COMPETE_QUERY|";
        data.append(table.toStdString());
        sendMessage(data);
    }

    /**
     * @brief 结束游戏, 断开自动接受信息的信号与槽
     *
     */
    void gameEnd()
    {
        disconnect(socket, &QTcpSocket::readyRead, this,
                   &TCPClient::readMultiPlayerMessage);
        emit toMain();
    }

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
