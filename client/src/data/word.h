#ifndef WORD_H
#define WORD_H

#include "../tcpclient.h"
#include "basicInfo.h"
#include <QtSql>
#include <fstream>

/**
 * @brief 单词信息类
 *
 */
class Word {
private:
    //    sqlite::database db;
    static Word *_instance; /// 单词单实例
    //    Word(const string path = "word.db"):db(path.c_str()){}
    QSqlDatabase db; /// 数据库
    /**
     * @brief 私有化单例构造函数
     *
     * @param path 路径
     */
    //    Word(const string path = "./word.db")
    //    {
    //        if (QSqlDatabase::contains("words_connection"))
    //            db = QSqlDatabase::database("words_connection");
    //        else
    //            db = QSqlDatabase::addDatabase("QSQLITE", "words_onnection");
    //        db.setDatabaseName(path.c_str());
    //        if (!db.open()) {
    //            throw db.lastError();
    //        }
    //    }
    Word() = default;

public:
    /**
     * @brief 获得单实例
     *
     * @return Word& 返回实例
     */
    static Word &instance();
    /**
     * @brief 删除实例
     *
     */
    static void destroy();

    /**
     * @brief 插入新单词
     *
     * @param wi 单词信息
     */
    //    void insert(const WordInfo &wi)
    //    {
    //        auto query =
    //            QString(
    //                "INSERT INTO Word (word,builder,len) VALUES
    //                ('%1','%2','%3');") .arg(QString::fromStdString(wi.word))
    //                .arg(QString::fromStdString(wi.builder))
    //                .arg(QString::fromStdString(std::to_string(wi.len)));
    //        QSqlQuery sqlQuery("words_connection", db);
    //        sqlQuery.prepare(query);
    //        if (!sqlQuery.exec()) {
    //            throw sqlQuery.lastError();
    //        }
    //        //        db << "INSERT INTO Word (word,builder,len) VALUES
    //        (?,?,?); "
    //        //           << wi.word << wi.builder << wi.len;
    //    }

    bool insert(const WordInfo &wi) {
        string data = "INSERT_WORD|";
        data.append(wi.word + "," + wi.builder + "," + std::to_string(wi.len));
        qDebug() << "insert word";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "INSERT_SUCCEEDED") {
            qDebug() << "insert failed";
            return false;
        }
        return true;
    }

    /**
     * @brief Get the Word object
     *
     * @param min 最小长度
     * @param max 最大长度
     * @return auto 单词信息
     */
    //    auto getWord(int min, int max)
    //    {
    //        WordInfo wi;
    //        QString query = QString("SELECT word, builder, fail_time,
    //        pass_time "
    //                                "FROM Word WHERE (len>='%1' and len<=%2) "
    //                                "ORDER BY RANDOM() LIMIT 1; ")
    //                            .arg(QString::number(min))
    //                            .arg(QString::number(max));
    //        QSqlQuery sqlQuery("words_connection", db);
    //        sqlQuery.prepare(query);
    //        if (sqlQuery.exec()) {
    //            if (sqlQuery.next()) {
    //                wi.word = sqlQuery.value(0).toString().toStdString();
    //                wi.builder = sqlQuery.value(1).toString().toStdString();
    //                wi.fail_time = sqlQuery.value(2).toInt();
    //                wi.pass_time = sqlQuery.value(3).toInt();
    //            }
    //        }
    //        return wi;
    //    }

    auto getWord(int min, int max) {
        WordInfo wi;
        string data = "GET_WORD|";
        data.append(std::to_string(min) + "," + std::to_string(max));
        qDebug() << "get word";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "WORD") {
            qDebug() << "get w failed";
        } else {
            qDebug() << "get w succeeded";
            wi.word = result.at(1).at(0).toStdString();
            wi.builder = result.at(1).at(1).toStdString();
            wi.fail_time = result.at(1).at(2).toInt();
            wi.pass_time = result.at(1).at(3).toInt();
            wi.len = result.at(1).at(4).toInt();
        }
        return wi;
    }

    /**
     * @brief Get the Words table
     *
     * @param model 查询模型
     * @param username 要查询的用户名
     */
    //    void getWordMakeTable(QVector<QVector<QString>> &model, string
    //    username) {
    //        QString query = QString("SELECT word,fail_time,pass_time "
    //                                "FROM Word WHERE builder='%1' ORDER BY
    //                                ID;")
    //                            .arg(QString::fromStdString(username));
    //        QSqlQuery qry("words_connection", db);
    //        qry.prepare(query);
    //        if (qry.exec()) {
    //            while (qry.next()) {
    //                QVector<QString> line;
    //                line.push_back(qry.value(0).toString());
    //                line.push_back(qry.value(1).toString());
    //                line.push_back(qry.value(2).toString());
    //                model.push_back(line);
    //            }
    //        }
    //    }

    void getWordMakeTable(QVector<QVector<QString>> &model, string username) {
        string data = "GET_WORD_TABLE|";
        data.append(username);
        qDebug() << "getwordtable";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "WORD_TABLE") {
            qDebug() << "get w table failed";
        } else {
            qDebug() << "get w table succeeded";
            result.erase(result.begin());
            model = result;
        }
    }

    /**
     * @brief 更新数据库的单词信息
     *
     * @param wordInfo 单词信息
     */
    //    void updateWord(WordInfo &worINSERT_SUCCEEDdInfo) {
    //        QString query = QString("UPDATE Word "
    //                                "SET fail_time='%1', pass_time='%2' "
    //                                "WHERE word='%3';")
    //                            .arg(wordInfo.fail_time)
    //                            .arg(wordInfo.pass_time)
    //                            .arg(QString(wordInfo.word.c_str()));
    //        QSqlQuery sqlQuery("words_connection", db);
    //        sqlQuery.prepare(query);
    //        if (!sqlQuery.exec()) {
    //            throw sqlQuery.lastError();
    //        }
    //    }

    void updateWord(WordInfo &wordInfo) {
        string data = "UPDATE_WORD|";
        data.append(std::to_string(wordInfo.fail_time) + "," +
                    std::to_string(wordInfo.pass_time) + "," + wordInfo.word);
        qDebug() << "update word";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "UPDATE_SUCCEEDED") {
            qDebug() << "update failed";
        } else {
            qDebug() << "update succeeded";
        }
    }
};

#endif // WORD_H
