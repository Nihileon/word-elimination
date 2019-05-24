/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 18:13:25
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 18:39:18
 */
#ifndef LOGIN_H
#define LOGIN_H

#include "../tcpclient.h"
#include "basicInfo.h"
#include <QString>
#include <QVariant>
#include <QtSql>
#include <iostream>

/**
 * @brief 用于处理用户信息的类
 */
class User {
private:
    //    QSqlDatabase db; /// 数据库信息

    static User *_instance; /// 用户单实例
    /**
     * @brief 构造函数, 由于是单例, 所以将构造函数私有化
     * @param path
     */
    //    User(const string path = "./user.db") {
    //        if (QSqlDatabase::contains("qt_sql_default_connection"))
    //            db = QSqlDatabase::database("qt_sql_default_connection");
    //        else
    //            db = QSqlDatabase::addDatabase("QSQLITE");
    //        db.setDatabaseName(path.c_str());
    //        if (!db.open()) {
    //            throw db.lastError();
    //        }
    //    }

    User() = default;

public:
    /**
     * @brief Destroy the User object
     *
     */
    //    ~User() { db.close(); }
    ~User() = default;
    /**
     * @brief 单例模式, 获得单实例
     *
     * @return User&
     */
    static User &instance();

    /**
     * @brief 单例模式, 删除实例
     *
     */
    static void destroy();

    /**
     * @brief 获取信息之后的状态
     * 默认状态(即成功);用户不存在;密码错误;登陆成功(未使用);未知状态(未使用)
     *
     */
    typedef enum {
        DEFAULT_STATUS,
        USR_NOT_EXIST,
        PWD_WRONG,
        LOGIN_SUCCESS,
        UNKNOWN
    } Status;

    /**
     * @brief 插入用户信息, 即注册出题人或玩家
     * @param li 登陆信息LoginInfo
     */
    //    void insert(const LoginInfo &li) {
    //        switch (li.type) {
    //        case LoginInfo::WORD_BUILDER: {
    //            auto query = QString("INSERT INTO WordBuilder (user_login, "
    //                                 "user_pass) VALUES ( '%1' ,'%2');")
    //                             .arg(QString::fromStdString(li.usr))
    //                             .arg(QString::fromStdString(li.pwd));
    //            QSqlQuery sqlQuery;
    //            sqlQuery.prepare(query);
    //            if (!sqlQuery.exec()) {
    //                throw sqlQuery.lastError();
    //            }
    //            break;
    //        }
    //        case LoginInfo::CHALLENGER: {
    //            auto query = QString("INSERT INTO Challenger (user_login, "
    //                                 "user_pass) VALUES ('%1','%2');")
    //                             .arg(QString::fromStdString(li.usr))
    //                             .arg(QString::fromStdString(li.pwd));
    //            QSqlQuery sqlQuery;
    //            sqlQuery.prepare(query);
    //            if (!sqlQuery.exec()) {
    //                throw sqlQuery.lastError();
    //            }
    //            break;
    //        }
    //        }
    //    }

    bool insert(const LoginInfo &li) {
        string data = "";
        switch (li.type) {
        case LoginInfo::WORD_BUILDER:
            data.append("INSERT_WORDBUILDER|");
            break;

        case LoginInfo::CHALLENGER:
            data.append("INSERT_CHALLENGER|");
            break;
        }
        data.append(li.usr + "," + li.pwd);
        qDebug() << "insert user";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();


        if (result.empty() || result.at(0).at(0) != "INSERT_SUCCEEDED") {
            qDebug() << "insert failed";
            return false;
        }
        return true;
    }
    /**
     * @brief 判断用户是否在数据库中
     * @param loginInfo 登陆信息
     */
    //    bool isUser(const LoginInfo &loginInfo) {
    //        string userType;
    //        if (loginInfo.type == LoginInfo::WORD_BUILDER) {
    //            userType = "WordBuilder";
    //        } else if (loginInfo.type == LoginInfo::CHALLENGER) {
    //            userType = "Challenger";
    //        }

    //        QString query =
    //            QString(
    //                "SELECT COUNT(*), user_pass FROM '%1' WHERE
    //                user_login='%2';") .arg(QString::fromStdString(userType))
    //                .arg(QString::fromStdString(loginInfo.usr));
    //        QSqlQuery sqlQuery;
    //        sqlQuery.prepare(query);
    //        sqlQuery.exec();
    //        if (sqlQuery.next()) {
    //            int is_exist = sqlQuery.value(0).toInt();
    //            string user_pass = sqlQuery.value(1).toString().toStdString();
    //            if (is_exist == 1 && user_pass == loginInfo.pwd) {
    //                return true;
    //            }
    //        }
    //        return false;
    //    }

    bool isUser(const LoginInfo &loginInfo) {
        string data = "IS_USER|";
        if (loginInfo.type == LoginInfo::WORD_BUILDER) {
            data.append("WordBuilder"
                        ",");
        } else if (loginInfo.type == LoginInfo::CHALLENGER) {
            data.append("Challenger"
                        ",");
        }
        data.append(loginInfo.usr + "," + loginInfo.pwd);
        qDebug() << "is user";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "USER") {
            return false;
        } else {
            return true;
        }
    }

    /**
     * @brief 获得出题人信息
     * @param loginInfo 登陆信息
     */
    //    auto getWordBuilder(const LoginInfo &loginInfo) {
    //        WordBuilder wb;
    //        wb.usr = loginInfo.usr;
    //        QString query =
    //            QString("SELECT level, exp, build_word, word_pass, word_fail"
    //                    " FROM WordBuilder WHERE user_login='%1';")
    //                .arg(QString::fromStdString(loginInfo.usr));
    //        QSqlQuery sqlQuery;
    //        sqlQuery.prepare(query);
    //        if (sqlQuery.exec()) {
    //            if (sqlQuery.next()) {
    //                wb.level = sqlQuery.value(0).toInt();
    //                wb.exp = sqlQuery.value(1).toInt();
    //                wb.build_word = sqlQuery.value(2).toInt();
    //                wb.word_pass = sqlQuery.value(3).toInt();
    //                wb.word_fail = sqlQuery.value(4).toInt();
    //            } else {
    //                throw sqlQuery.lastError();
    //            }
    //        } else {
    //            throw sqlQuery.lastError();
    //        }
    //        return wb;
    //    }
    auto getWordBuilder(const LoginInfo &loginInfo) {
        WordBuilder wb;
        wb.usr = loginInfo.usr;
        string data = "GET_WORDBUILDER|";
        data.append(loginInfo.usr);
        qDebug() << "getWordBuilder";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "WORDBUILDER") {
            qDebug() << "get wb failed";
        } else {
            qDebug() << "get wb succeeded";
            wb.level = result.at(1).at(0).toInt();
            wb.exp = result.at(1).at(1).toInt();
            wb.build_word = result.at(1).at(2).toInt();
            wb.word_pass = result.at(1).at(3).toInt();
            wb.word_fail = result.at(1).at(4).toInt();
        }
        return wb;
    }

    /**
     * @brief 获得玩家信息
     * @param loginInfo 登录信息
     */
    //    auto getChallenger(const LoginInfo &loginInfo) {
    //        Challenger c;
    //        c.usr = loginInfo.usr;
    //        QString query =
    //            QString("SELECT level, exp, card_pass, card_fail,
    //            word_eliminate"
    //                    " FROM Challenger WHERE user_login='%1';")
    //                .arg(QString::fromStdString(loginInfo.usr));
    //        QSqlQuery sqlQuery;
    //        sqlQuery.prepare(query);
    //        if (sqlQuery.exec()) {
    //            if (sqlQuery.next()) {
    //                c.level = sqlQuery.value(0).toInt();
    //                c.exp = sqlQuery.value(1).toInt();
    //                c.card_pass = sqlQuery.value(2).toInt();
    //                c.card_fail = sqlQuery.value(3).toInt();
    //                c.word_eliminate = sqlQuery.value(4).toInt();
    //            } else {
    //                throw sqlQuery.lastError();
    //            }
    //        } else {
    //            throw sqlQuery.lastError();
    //        }
    //        return c;
    //    }

    auto getChallenger(const LoginInfo &loginInfo) {
        Challenger c;
        c.usr = loginInfo.usr;

        string data = "GET_CHALLENGER|";
        data.append(loginInfo.usr);
        qDebug() << "getchallenger";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "CHALLENGER") {
            qDebug() << "get c failed";
        } else {
            qDebug() << "get c succeeded";
            c.level = result.at(1).at(0).toInt();
            c.exp = result.at(1).at(1).toInt();
            c.card_pass = result.at(1).at(2).toInt();
            c.card_fail = result.at(1).at(3).toInt();
            c.word_eliminate = result.at(1).at(4).toInt();
        }
        return c;
    }

    /**
     * @brief 获得构建玩家排行榜的模型
     * @param model 用于构造排行榜的模型
     */
    //    void getChallengerMakeTable(QVector<QVector<QString>> &model) {
    //        QString query =
    //            "SELECT user_login, level, exp, card_pass, word_eliminate "
    //            "FROM Challenger ORDER BY exp DESC;";
    //        QSqlQuery qry;
    //        qry.prepare(query);
    //        if (qry.exec()) {
    //            while (qry.next()) {
    //                QVector<QString> tmp;
    //                tmp.push_back(qry.value(0).toString());
    //                tmp.push_back(qry.value(1).toString());
    //                tmp.push_back(qry.value(2).toString());
    //                tmp.push_back(qry.value(3).toString());
    //                tmp.push_back(qry.value(4).toString());
    //                model.push_back(tmp);
    //            }
    //        }
    //    }

    void getChallengerMakeTable(QVector<QVector<QString>> &model) {
        string data = "GET_CHALLENGER_TABLE";
        qDebug() << "getchallengertable";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "CHALLENGER_TABLE") {
            qDebug() << "get c table failed";
        } else {
            qDebug() << "get c table succeeded";
            result.erase(result.begin());
            model = result;
        }
    }

    /**
     * @brief 获得构建出题人排行榜的模型
     * @param model 用于构建排行榜的模型
     */
    void getWordBuilderMakeTable(QVector<QVector<QString>> &model) {
        string data = "GET_WORDBUILDER_TABLE";
qDebug() << "getwbtable";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "WORDBUILDER_TABLE") {
            qDebug() << "get wb table failed";
        } else {
            qDebug() << "get wb table succeeded";
            result.erase(result.begin());
            model = result;
        }
    }

    /**
     * @brief 更新出题人信息
     *
     * @param wb 出题人信息
     */
    //    void updateUser(const WordBuilder &wb) {
    //        if (wb.exp < 0) {
    //            throw "exp overflow";
    //        }
    //        QString query = QString("UPDATE WordBuilder"
    //                                " SET level='%1', exp='%2',
    //                                build_word='%3'" " WHERE user_login =
    //                                '%4';")
    //                            .arg(wb.level)
    //                            .arg(wb.exp)
    //                            .arg(wb.build_word)
    //                            .arg(QString::fromStdString(wb.usr));
    //        QSqlQuery sqlQuery;
    //        sqlQuery.prepare(query);
    //        if (!sqlQuery.exec()) {
    //            throw sqlQuery.lastError();
    //        }
    //    }
    void updateUser(const WordBuilder &wb) {
        if (wb.exp < 0) {
            throw "exp overthrow";
        }
        string data = "UPDATE_WORDBUILDER|";
        data.append(std::to_string(wb.level) + "," + std::to_string(wb.exp) +
                    "," + std::to_string(wb.build_word) + "," + wb.usr);
        qDebug() << "updateuser";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "UPDATE_SUCCEEDED") {
            qDebug() << "update failed";
        } else {
            qDebug() << "update succeeded";
        }
    }

    /**
     * @brief 更新玩家信息
     *
     * @param 玩家信息
     */
    //    void updateUser(const Challenger &c) {
    //        if (c.exp < 0) {
    //            throw "exp overthrow";
    //        }
    //        QString query = QString("UPDATE Challenger"
    //                                " SET level='%1', exp='%2',
    //                                card_pass='%3', " "card_fail='%4',
    //                                word_eliminate='%5'" " WHERE
    //                                user_login='%6';")
    //                            .arg(c.level)
    //                            .arg(c.exp)
    //                            .arg(c.card_pass)
    //                            .arg(c.card_fail)
    //                            .arg(c.word_eliminate)
    //                            .arg(QString::fromStdString(c.usr));
    //        QSqlQuery sqlQuery;
    //        sqlQuery.prepare(query);
    //        if (!sqlQuery.exec()) {
    //            throw sqlQuery.lastError();
    //        }
    //    }
    void updateUser(const Challenger &c) {
        if (c.exp < 0) {
            throw "exp overthrow";
        }
        string data = "UPDATE_CHALLENGER|";
        data.append(std::to_string(c.level) + "," + std::to_string(c.exp) +
                    "," + std::to_string(c.card_pass) + "," +
                    std::to_string(c.card_fail) + "," +
                    std::to_string(c.word_eliminate) + "," + c.usr);
        qDebug() << "update challenger";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "UPDATE_SUCCEEDED") {
            qDebug() << "update failed";
        } else {
            qDebug() << "update succeeded";
        }
    }

    /**
     * @brief getSearchWordBuilderMakeTable
     * @param model sql模型
     * @param former 搜索的类型
     * @param latter 搜索的值
     */
    //    void getSearchWordBuilderMakeTable(QVector<QVector<QString>> &model,
    //                                       std::string former, std::string
    //                                       latter) {
    //        QString query = QString("SELECT user_login, level, exp, build_word
    //        "
    //                                "FROM WordBuilder where %1='%2';")
    //                            .arg(QString::fromStdString(former))
    //                            .arg(QString::fromStdString(latter));
    //        QSqlQuery qry;
    //        qry.prepare(query);
    //        if (qry.exec()) {
    //            while (qry.next()) {
    //                QVector<QString> tmp;
    //                tmp.push_back(qry.value(0).toString());
    //                tmp.push_back(qry.value(1).toString());
    //                tmp.push_back(qry.value(2).toString());
    //                tmp.push_back(qry.value(3).toString());
    //                model.push_back(tmp);
    //            }
    //        }
    //    }
    void getSearchWordBuilderMakeTable(QVector<QVector<QString>> &model,
                                       std::string former, std::string latter) {
        string data = "GET_SEARCH_WORDBUILDER|";
        data.append(former + "," + latter);
        qDebug() << "getsearchwbtable";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "SEARCH_WORDBUILDER") {
            qDebug() << "get search wb table failed";
        } else {
            qDebug() << "get search wb table succeeded";
            result.erase(result.begin());
            model = result;
        }
    }

    /**
     * @brief getSearchChallengerMakeTable
     * @param model sql模型
     * @param former 搜索的类型
     * @param latter 搜索的值
     */
    //    void getSearchChallengerMakeTable(QVector<QVector<QString>> &model,
    //                                      std::string former, std::string
    //                                      latter) {
    //        QString query =
    //            QString("SELECT user_login, level, exp, card_pass,
    //            word_eliminate "
    //                    "FROM Challenger where %1='%2';")
    //                .arg(QString::fromStdString(former))
    //                .arg(QString::fromStdString(latter));
    //        QSqlQuery qry;
    //        qry.prepare(query);
    //        if (qry.exec()) {
    //            while (qry.next()) {
    //                QVector<QString> tmp;
    //                tmp.push_back(qry.value(0).toString());
    //                tmp.push_back(qry.value(1).toString());
    //                tmp.push_back(qry.value(2).toString());
    //                tmp.push_back(qry.value(3).toString());
    //                tmp.push_back(qry.value(4).toString());
    //                model.push_back(tmp);
    //            }
    //        }
    //    }

    void getSearchChallengerMakeTable(QVector<QVector<QString>> &model,
                                      std::string former, std::string latter) {
        string data = "GET_SEARCH_CHALLENGER|";
        data.append(former + "," + latter);
        qDebug() << "getsearchchallengertable";
        TCPClient::instance().sendMessage(data);
        QVector<QVector<QString>> result = TCPClient::instance().readMessage();
        if (result.empty() || result.at(0).at(0) != "SEARCH_CHALLENGER") {
            qDebug() << "get search c table failed";
        } else {
            qDebug() << "get search c table succeeded";
            result.erase(result.begin());
            model = result;
        }
    }
};

#endif // LOGIN_H
