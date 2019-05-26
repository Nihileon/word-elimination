#include "tcpclient.h"

TCPClient *TCPClient::_instance = nullptr;

void TCPClient::connectServer() {
    quint16 port = 8899;
    socket->connectToHost("127.0.0.1", port);
    if (socket->waitForConnected(10000)) {
        qDebug() << "connected";
    } else {
        qDebug() << "not connect";
    }
}

TCPClient &TCPClient::instance() {
    if (_instance == nullptr) {
        _instance = new TCPClient();
    }
    return *_instance;
}

void TCPClient::destroy() {
    if (_instance != nullptr) {
        delete _instance;
    }
    return;
}

TCPClient::~TCPClient() { delete socket; }

void TCPClient::sendMessage(std::string message) {
    qDebug() << "send message";
    socket->write(message.c_str());
    socket->flush();
    socket->waitForBytesWritten();
}

QVector<QVector<QString>> TCPClient::readMessage() {
    QVector<QVector<QString>> table;
    if (socket->waitForReadyRead()) {
        QString result = socket->readLine();
        table = transformation::stringToTable(result.toStdString());
    } else {
        qDebug() << "received nothing";
    }
    return table;
}

void TCPClient::readMultiPlayerMessage() {
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

void TCPClient::sendBeginMatchingRequest(QVariant info) {
    qDebug() << "send begin matching request";
    connect(socket, &QTcpSocket::readyRead, this,
            &TCPClient::readMultiPlayerMessage);
    auto challenger = info.value<Challenger>();
    std::string qs = "MULTIPLAYER_QUERY|";
    qs.append(challenger.usr);
    sendMessage(qs.c_str());
}

void TCPClient::sendEndMatchingRequest(QVariant info) {
    disconnect(socket, &QTcpSocket::readyRead, this,
               &TCPClient::readMultiPlayerMessage);
    auto challenger = info.value<Challenger>();

    std::string qs = "END_MULTIPLAYER_QUERY|";
    qs.append(challenger.usr);
    sendMessage(qs.c_str());
}

void TCPClient::sendRefuseCompeteQuery(QString table) {
    qDebug() << "sendRefuseCompeteQuery";
    std::string data = "REFUSE_COMPETE_QUERY|";
    data.append(table.toStdString());
    sendMessage(data);
}

void TCPClient::sendAgreeCompeteQuery(QString table) {
    qDebug() << "sendAgreeCompeteQuery";
    std::string data = "AGREE_COMPETE_QUERY|";
    data.append(table.toStdString());
    sendMessage(data);
}

void TCPClient::gameEnd() {
    disconnect(socket, &QTcpSocket::readyRead, this,
               &TCPClient::readMultiPlayerMessage);
    emit toMain();
}
