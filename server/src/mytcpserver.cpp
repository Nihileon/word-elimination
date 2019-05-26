#include "mytcpserver.h"

void MyTcpServer::parseAndReply(MySocket *socket, QString &result) {
    auto table = transformation::stringToTable(result.toStdString());
    auto type = table.at(0).at(0);
    table.erase(table.begin());
    qDebug() << type << socket->socketDescriptor();
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
        sendMessage(socket, data);
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
        sendMessage(socket, data);
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
            socket->setUserName(li.usr);
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
        sendMessage(socket, data);
    } else if (type == "GET_CHALLENGER") {
        LoginInfo li;
        li.usr = table.at(0).at(0).toStdString();
        Challenger c = User::instance().getChallenger(li);
        QString data = "CHALLENGER|";

        data.append(QString::number(c.level) + "," + QString::number(c.exp) +
                    "," + QString::number(c.card_pass) + "," +
                    QString::number(c.card_fail) + "," +
                    QString::number(c.word_eliminate));
        sendMessage(socket, data);
    } else if (type == "GET_WORDBUILDER_TABLE") {
        QString data = "WORDBUILDER_TABLE|";
        QVector<QVector<QString>> result;
        User::instance().getWordBuilderMakeTable(result);
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(socket, data);
    } else if (type == "GET_CHALLENGER_TABLE") {
        QString data = "CHALLENGER_TABLE|";
        QVector<QVector<QString>> result;
        User::instance().getChallengerMakeTable(result);
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(socket, data);

    } else if (type == "GET_SEARCH_WORDBUILDER") {
        QString data = "SEARCH_WORDBUILDER|";
        QVector<QVector<QString>> result;
        User::instance().getSearchWordBuilderMakeTable(
            result, table.at(0).at(0).toStdString(),
            table.at(0).at(1).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(socket, data);

    } else if (type == "GET_SEARCH_CHALLENGER") {
        QString data = "SEARCH_CHALLENGER|";
        QVector<QVector<QString>> result;
        User::instance().getSearchChallengerMakeTable(
            result, table.at(0).at(0).toStdString(),
            table.at(0).at(1).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(socket, data);

    } else if (type == "UPDATE_WORDBUILDER") {
        QString data = "UPDATE_SUCCEEDED";
        WordBuilder wb;
        wb.level = table.at(0).at(0).toInt();
        wb.exp = table.at(0).at(1).toInt();
        wb.build_word = table.at(0).at(2).toInt();
        wb.usr = table.at(0).at(3).toStdString();
        User::instance().updateUser(wb);
        sendMessage(socket, data);

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
        sendMessage(socket, data);

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
        sendMessage(socket, data);

    } else if (type == "GET_WORD") {
        QString data = "WORD|";
        WordInfo wi = Word::instance().getWord(table.at(0).at(0).toInt(),
                                               table.at(0).at(1).toInt());

        data.append(QString::fromStdString(wi.word) + "," +
                    QString::fromStdString(wi.builder) + "," +
                    QString::number(wi.fail_time) + "," +
                    QString::number(wi.pass_time) + "," +
                    QString::number(wi.len));
        sendMessage(socket, data);

    } else if (type == "GET_WORD_TABLE") {
        QString data = "WORD_TABLE|";
        QVector<QVector<QString>> result;
        Word::instance().getWordMakeTable(result,
                                          table.at(0).at(0).toStdString());
        data.append(
            QString::fromStdString(transformation::tableToString(result)));
        sendMessage(socket, data);

    } else if (type == "UPDATE_WORD") {
        QString data = "UPDATE_SUCCEEDED";
        WordInfo wi;
        wi.fail_time = table.at(0).at(0).toInt();
        wi.pass_time = table.at(0).at(1).toInt();
        wi.word = table.at(0).at(2).toStdString();
        sendMessage(socket, data);
    } else if (type == "MULTIPLAYER_QUERY") {
        addChallengerSlot(socket->socketDescriptor(), table.at(0).at(0));
    } else if (type == "END_MULTIPLAYER_QUERY") {
        deleteChallengerSlot(socket->socketDescriptor());
    } else if (type == "COMPETE_QUERY") {
        sendCompeteQuery(socket->socketDescriptor(), table.at(0).at(0));
    } else if (type == "REFUSE_COMPETE_QUERY") {
        // TODO send sender refuse message
        users.insert(table.at(0).at(2).toInt(), table.at(0).at(0));
        users.insert(table.at(1).at(2).toInt(), table.at(1).at(0));
        renewOnlineTable();
        delayMsec(20);
    } else if (type == "AGREE_COMPETE_QUERY") {
        auto senderHandle = table.at(0).at(2).toInt();
        auto receiverHandle = table.at(1).at(2).toInt();
        competitorPair cp(table.at(0).at(0), senderHandle, table.at(1).at(0),
                          receiverHandle);
        currentOnline.insert(senderHandle, receiverHandle);
        WordInfo wi = Word::instance().getWord(6, 10);
        QString data = "MULTIPALYER_GAME_BEGIN|";
        data.append(QString::fromStdString(wi.word) + "," +
                    QString::number(wi.len) + "," +
                    QString::fromStdString(wi.builder) + "," +
                    QString::number(wi.fail_time));

        sendMessage(clients.value(senderHandle), data);
        sendMessage(clients.value(receiverHandle), data);
    } else if (type == "WORD_QUIT") {
        QString data = "DOUBLE_GAME_END";
        auto handleA = socket->socketDescriptor();

        if (currentOnline.contains(handleA)) {
            auto handleB = currentOnline.value(handleA);
            sendMessage(clients.value(handleB), data);
            currentOnline.remove(handleA);
        } else {
            auto handleB = currentOnline.key(handleA);
            sendMessage(clients.value(handleB), data);
            currentOnline.remove(handleB);
        }
    } else if (type == "WORD_CORRECT") {
        QString data = "DOUBLE_GAME_END";
        LoginInfo li;
        li.usr = socket->getUserName();
        Challenger ci = User::instance().getChallenger(li);
        ci.exp += 100;
        User::instance().updateUser(ci);
        auto handleA = socket->socketDescriptor();
        if (currentOnline.contains(handleA)) {
            auto handleB = currentOnline.value(handleA);
            sendMessage(clients.value(handleB), data);
            currentOnline.remove(handleA);
        } else {
            auto handleB = currentOnline.key(handleA);
            sendMessage(clients.value(handleB), data);
            currentOnline.remove(handleB);
        }
        qDebug() << "parse failed";
    }
}
