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
    TCPClient() : socket(new QTcpSocket) { connectServer(); }
    static TCPClient *_instance;

public:
    static TCPClient &instance();
    static void destroy();
    void connectServer() {
        quint16 port = 8899;
        socket->connectToHost("127.0.0.1", port);
        if (socket->waitForConnected(10000)) {
            qDebug() << "connected";
        } else {
            qDebug() << "not connect";
        }
    }
    ~TCPClient() { delete socket; }

    void sendMessage(std::string message) {
        qDebug() << "send message";
        socket->write(message.c_str());
        socket->flush();
        socket->waitForBytesWritten();
    }


    QVector<QVector<QString>> readMessage() {
        QVector<QVector<QString>> table;
        if (socket->waitForReadyRead()) {
            QString result = socket->readLine();
            table = transformation::stringToTable(result.toStdString());
        } else {
            qDebug() << "received nothing";
        }
        return table;
    }

    void readMultiPlayerMessage() {
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

    void sendBeginMatchingRequest(QVariant qv) {
        qDebug() << "send begin match request";
        connect(socket, &QTcpSocket::readyRead, this,
                &TCPClient::readMultiPlayerMessage);
        auto challenger = qv.value<Challenger>();
        std::string qs = "MULTIPLAYER_QUERY|";
        qs.append(challenger.usr);
        sendMessage(qs.c_str());
    }

    void sendEndMatchingRequest(QVariant qv) {
        disconnect(socket, &QTcpSocket::readyRead, this,
                   &TCPClient::readMultiPlayerMessage);
        auto challenger = qv.value<Challenger>();

        std::string qs = "END_MULTIPLAYER_QUERY|";
        qs.append(challenger.usr);
        sendMessage(qs.c_str());
    }

    void sendRefuseCompeteQuery(QString table) {
        qDebug() << "sendRefuseCompeteQuery";
        std::string data = "REFUSE_COMPETE_QUERY|";
        data.append(table.toStdString());
        sendMessage(data);
    }

    void sendAgreeCompeteQuery(QString table){
        qDebug() << "sendAgreeCompeteQuery";
        std::string data = "AGREE_COMPETE_QUERY|";
        data.append(table.toStdString());
        sendMessage(data);
    }

    void gameEnd(){
        disconnect(socket, &QTcpSocket::readyRead, this,
                   &TCPClient::readMultiPlayerMessage);
        emit toMain();
    }

    QTcpSocket *socket;
signals:
    void sendMultiPlayerTable(QVector<QVector<QString>> table);
    void sendCompeteRequest(QVector<QVector<QString>> table);
    void beginMultiPlayerGame(QVector<QVector<QString>> table);
    void toMain();
};

#endif // TCPCLIENT_H
