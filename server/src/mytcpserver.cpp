#include "mytcpserver.h"

MyTcpServer *MyTcpServer::_instance = nullptr;
MyTcpServer::MyTcpServer(QObject *parent)
    : QObject(parent), server(new QTcpServer(this)),
      socket(new QTcpSocket(this)) {
    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

MyTcpServer &MyTcpServer::instance() {
    if (_instance == nullptr) {
        _instance = new MyTcpServer();
    }
    return *_instance;
}

void MyTcpServer::destroy() {
    if (_instance != nullptr) {
        delete _instance;
    }
    return;
}

void MyTcpServer::init() {
    if (!server->listen(QHostAddress::LocalHost, 8899)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started!";
    }
}

void MyTcpServer::disconnect() {
    socket->close();
    socket->waitForDisconnected();
}

void MyTcpServer::parseAndReply(QString &result) {
    auto table = transformation::stringToTable(result.toStdString());
    auto type = table.at(0).at(0);
    table.erase(table.begin());
    if (type == "INSERT_CHALLENGER") {
        QString data = "";
        LoginInfo li;
        li.type = LoginInfo::CHALLENGER;
        li.usr = table.at(0).at(0).toStdString();
        li.pwd = table.at(0).at(1).toStdString();
        try {
            User::instance().insert(li);
            data.append("INSERT_SUCCEEDED");
        } catch (QSqlError &e) {
            data.append("INSERT_UNSUCCEEDED");
        }
        sendMessage(data);
    } else if (type == "INSERT_WORDBUILDER") {
        QString data = "";
        LoginInfo li;
        li.type = LoginInfo::WORD_BUILDER;
        li.usr = table.at(0).at(0).toStdString();
        li.pwd = table.at(0).at(1).toStdString();
        try {
            User::instance().insert(li);
            data.append("INSERT_SUCCEEDED");
        } catch (QSqlError &e) {
            data.append("INSERT_UNSUCCEEDED");
        }
        sendMessage(data);
    } else if (type == "IS_USER") {
        LoginInfo li;
        if (table.at(0).at(0) == "WordBuilder") {
            li.type = LoginInfo::WORD_BUILDER;
        } else if (table.at(0).at(0) == "Challenger") {
            li.type = LoginInfo::CHALLENGER;
        }
        li.usr = table.at(0).at(1).toStdString();
        li.pwd = table.at(0).at(2).toStdString();
        if (User::instance().isUser(li)) {
            socket->write("USER");
        } else {
            socket->write("NOT_USER");
        }
        socket->flush();
        socket->waitForBytesWritten();
    } else if (type == "GET_WORDBUILDER") {
        LoginInfo li;
        li.usr = table.at(0).at(0).toStdString();
        WordBuilder wb = User::instance().getWordBuilder(li);
        QString data = "WORDBUILDER|";

        data.append(QString::number(wb.level) + "," + QString::number(wb.exp) +
                    "," + QString::number(wb.build_word) + "," +
                    QString::number(wb.word_pass) + "," +
                    QString::number(wb.word_fail));
        sendMessage(data);
    } else if (type == "GET_CHALLENGER") {
        LoginInfo li;
        li.usr = table.at(0).at(0).toStdString();
        Challenger c = User::instance().getChallenger(li);
        QString data = "CHALLENGER|";

        data.append(QString::number(c.level) + "," + QString::number(c.exp) +
                    "," + QString::number(c.card_pass) + "," +
                    QString::number(c.card_fail) + "," +
                    QString::number(c.word_eliminate));
        sendMessage(data);
    } else if (type == "GET_WORDBUILDER_TABLE") {
        QString data = "WORDBUILDER_TABLE|";
        QVector<QVector<QString>> result;
        User::instance().getWordBuilderMakeTable(result);
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(data);
    } else if (type == "GET_CHALLENGER_TABLE") {
        QString data = "CHALLENGER_TABLE|";
        QVector<QVector<QString>> result;
        User::instance().getChallengerMakeTable(result);
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(data);

    } else if (type == "GET_SEARCH_WORDBUILDER") {
        QString data = "SEARCH_WORDBUILDER|";
        QVector<QVector<QString>> result;
        User::instance().getSearchWordBuilderMakeTable(
            result, table.at(0).at(0).toStdString(),
            table.at(0).at(1).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(data);

    } else if (type == "GET_SEARCH_CHALLENGER") {
        QString data = "SEARCH_CHALLENGER|";
        QVector<QVector<QString>> result;
        User::instance().getSearchChallengerMakeTable(
            result, table.at(0).at(0).toStdString(),
            table.at(0).at(1).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(data);

    } else if (type == "UPDATE_WORDBUILDER") {
        QString data = "UPDATE_SUCCEEDED";
        WordBuilder wb;
        wb.level = table.at(0).at(0).toInt();
        wb.exp = table.at(0).at(1).toInt();
        wb.build_word = table.at(0).at(2).toInt();
        wb.usr = table.at(0).at(3).toStdString();
        User::instance().updateUser(wb);
        sendMessage(data);

    } else if (type == "UPDATE_CHALLENGER") {
        QString data = "UPDATE_SUCCEEDED";
        Challenger c;
        c.level = table.at(0).at(0).toInt();
        c.exp = table.at(0).at(1).toInt();
        c.card_pass = table.at(0).at(2).toInt();
        c.card_fail = table.at(0).at(3).toInt();
        c.word_eliminate = table.at(0).at(4).toInt();
        c.usr = table.at(0).at(5).toStdString();
        User::instance().updateUser(c);
        sendMessage(data);

    } else if (type == "INSERT_WORD") {
        QString data = "";
        WordInfo wi;
        wi.word = table.at(0).at(0).toStdString();
        wi.builder = table.at(0).at(1).toStdString();
        wi.len = table.at(0).at(2).toInt();
        try {
            Word::instance().insert(wi);
            data.append("INSERT_SUCCEEDED");
        } catch (QSqlError &e) {
            data.append("INSERT_UNSUCCEEDED");
        }
        sendMessage(data);

    } else if (type == "GET_WORD") {
        QString data = "WORD|";
        WordInfo wi = Word::instance().getWord(table.at(0).at(0).toInt(),
                                              table.at(0).at(1).toInt());

        data.append(QString::fromStdString(wi.word) + "," +
                    QString::fromStdString(wi.builder) + "," +
                    QString::number(wi.fail_time) + "," +
                    QString::number(wi.pass_time));
        sendMessage(data);

    } else if (type == "GET_WORD_TABLE") {
        QString data = "WORD_TABLE|";
        QVector<QVector<QString>> result;
        Word::instance().getWordMakeTable(result,
                                          table.at(0).at(0).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(data);

    } else if (type == "UPDATE_WORD") {
        QString data = "UPDATE_SUCCEEDED";
        WordInfo wi;
        wi.fail_time = table.at(0).at(0).toInt();
        wi.pass_time = table.at(0).at(1).toInt();
        wi.word = table.at(0).at(2).toStdString();
        sendMessage(data);
    } else {
        qDebug() << "parse failed";
    }
}

void MyTcpServer::run() {
    while (1) {
        QString data = readMessage();
        parseAndReply(data);
    }
}

void MyTcpServer::newConnection() {
    // need to grab the socket
    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readRead()), this, SLOT(readMessage()));
    connect(socket, SIGNAL(waitForBytesWritten()), this, SLOT(sendMessage()));
    //    socket->write("Hello client\r\n");
    //    socket->flush();

    //    socket->waitForBytesWritten(3000);

    //    socket->close();

    //    if (socket->readLine() == "start") {
    //        qDebug() << "start";
    //        socket->write("start");
    //        socket->flush();
    //        QString clientmove = "something";
    //        while (clientmove != "close") {
    //            char move[9];
    //            socket->write(move);
    //            socket->flush();
    //            socket->waitForBytesWritten(1000);
    //            socket->waitForReadyRead(10000);
    //            clientmove = socket->readLine();
    //            qDebug() << clientmove;
    //        }
    //    }
    //    socket->close();
    //    socket->waitForDisconnected(10900);
    MyTcpServer::instance().run();
//    MyTcpServer::instance().disconnect();
}

QString MyTcpServer::readMessage() {
    socket->waitForReadyRead(50000);
    qDebug() << "got readsignal" << socket->bytesAvailable() << "bytes";
    QString messsage = socket->readLine();
    return messsage;
}

void MyTcpServer::sendMessage(QString &data) {
    socket->write(data.toStdString().c_str());
    socket->flush();
    socket->waitForBytesWritten();
}
