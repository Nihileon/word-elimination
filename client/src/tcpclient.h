#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "data/transformation.h"
#include <QByteArray>
#include <QDataStream>
#include <QHostAddress>
#include <QTcpSocket>

class TCPClient {
private:
    TCPClient() : socket(new QTcpSocket) {
        connectServer();
    }
    static TCPClient *_instance;
public:
    static TCPClient& instance();
    static void destroy();
    void connectServer() {
        quint16 port = 8899;
        socket->connectToHost("127.0.0.1", port);
        if (socket->waitForConnected(10000)) {
            qDebug() << "connected";
//            socket->write("emmm");
//            socket->flush();
//            socket->waitForBytesWritten(1000);
        } else {
            qDebug() << "not connect";
        }
//        socket->waitForReadyRead(1000);
//        if (socket->readLine() == "start") {
//            QString servermove = "something";
//            while (servermove != "close") {
//                char move[9];
//                socket->waitForReadyRead(30000);
//                servermove = socket->readLine();
//                qDebug() << servermove;
//                socket->write(move);
//                socket->flush();
//                socket->waitForBytesWritten(10000);
//            }
//        }
//        socket->close();
//        socket->waitForDisconnected(1000);
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
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
