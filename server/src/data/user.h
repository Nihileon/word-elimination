/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 18:13:25
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 18:39:18
 */
#ifndef LOGIN_H
#define LOGIN_H

#include "basic.h"
#include <QString>
#include <QVariant>
#include <QtSql>
#include <iostream>

/**
 * @brief 用于处理用户信息的类
 */
class User {
private:
    QSqlDatabase db; /// 数据库信息

    static User *_instance; /// 用户单实例
    /**
     * @brief 构造函数, 由于是单例, 所以将构造函数私有化
     * @param path
     */
    User(const string path = "./user.db") {
        if (QSqlDatabase::contains("qt_sql_default_connection"))
            db = QSqlDatabase::database("qt_sql_default_connection");
        else
            db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.c_str());
        if (!db.open()) {
            throw db.lastError();
        }
    }

public:
    /**
     * @brief Destroy the User object
     *
     */
    ~User() { db.close(); }

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
    void insert(const LoginInfo &li) {
        switch (li.type) {
        case LoginInfo::WORD_BUILDER: {
            auto query = QString("INSERT INTO WordBuilder (user_login, "
                                 "user_pass) VALUES ( '%1' ,'%2');")
                             .arg(QString::fromStdString(li.usr))
                             .arg(QString::fromStdString(li.pwd));
            QSqlQuery sqlQuery;
            sqlQuery.prepare(query);
            if (!sqlQuery.exec()) {
                throw sqlQuery.lastError();
            }
            break;
        }
        case LoginInfo::CHALLENGER: {
            auto query = QString("INSERT INTO Challenger (user_login, "
                                 "user_pass) VALUES ('%1','%2');")
                             .arg(QString::fromStdString(li.usr))
                             .arg(QString::fromStdString(li.pwd));
            QSqlQuery sqlQuery;
            sqlQuery.prepare(query);
            if (!sqlQuery.exec()) {
                throw sqlQuery.lastError();
            }
            break;
        }
        }
    }
    /**
     * @brief 判断用户是否在数据库中
     * @param loginInfo 登陆信息
     */
    bool isUser(const LoginInfo &loginInfo) {
        string userType;
        if (loginInfo.type == LoginInfo::WORD_BUILDER) {
            userType = "WordBuilder";
        } else if (loginInfo.type == LoginInfo::CHALLENGER) {
            userType = "Challenger";
        }

        QString query =
            QString(
                "SELECT COUNT(*), user_pass FROM '%1' WHERE user_login='%2';")
                .arg(QString::fromStdString(userType))
                .arg(QString::fromStdString(loginInfo.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.exec();
        if (sqlQuery.next()) {
            int is_exist = sqlQuery.value(0).toInt();
            string user_pass = sqlQuery.value(1).toString().toStdString();
            if (is_exist == 1 && user_pass == loginInfo.pwd) {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief 获得出题人信息
     * @param loginInfo 登陆信息
     */
    auto getWordBuilder(const LoginInfo &loginInfo) {
        WordBuilder wb;
        wb.usr = loginInfo.usr;
        QString query =
            QString("SELECT level, exp, build_word, word_pass, word_fail"
                    " FROM WordBuilder WHERE user_login='%1';")
                .arg(QString::fromStdString(loginInfo.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                wb.level = sqlQuery.value(0).toInt();
                wb.exp = sqlQuery.value(1).toInt();
                wb.build_word = sqlQuery.value(2).toInt();
                wb.word_pass = sqlQuery.value(3).toInt();
                wb.word_fail = sqlQuery.value(4).toInt();
            } else {
                throw sqlQuery.lastError();
            }
        } else {
            throw sqlQuery.lastError();
        }
        return wb;
    }

    /**
     * @brief 获得构建玩家排行榜的模型
     * @param model 用于构造排行榜的模型
     */
    void getChallengerMakeTable(QVector<QVector<QString>> &model) {
        QString query =
            "SELECT user_login, level, exp, card_pass, word_eliminate "
            "FROM Challenger ORDER BY exp DESC;";
        QSqlQuery qry;
        qry.prepare(query);
        if (qry.exec()) {
            while (qry.next()) {
                QVector<QString> tmp;
                tmp.push_back(qry.value(0).toString());
                tmp.push_back(qry.value(1).toString());
                tmp.push_back(qry.value(2).toString());
                tmp.push_back(qry.value(3).toString());
                tmp.push_back(qry.value(4).toString());
                model.push_back(tmp);
            }
        }
    }

    /**
     * @brief 获得构建出题人排行榜的模型
     * @param model 用于构建排行榜的模型
     */
    void getWordBuilderMakeTable(QVector<QVector<QString>> &model) {
        QString query = "SELECT user_login, level, exp, build_word "
                        "FROM WordBuilder ORDER BY build_word DESC;";
        QSqlQuery qry;
        qry.prepare(query);
        if (qry.exec()) {
            while (qry.next()) {
                QVector<QString> tmp;
                tmp.push_back(qry.value(0).toString());
                tmp.push_back(qry.value(1).toString());
                tmp.push_back(qry.value(2).toString());
                tmp.push_back(qry.value(3).toString());
                model.push_back(tmp);
            }
        }
    }


    /**
     * @brief 获得玩家信息
     * @param loginInfo 登录信息
     */
    auto getChallenger(const LoginInfo &loginInfo) {
        Challenger c;
        c.usr = loginInfo.usr;
        QString query =
            QString("SELECT level, exp, card_pass, card_fail, word_eliminate"
                    " FROM Challenger WHERE user_login='%1';")
                .arg(QString::fromStdString(loginInfo.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                c.level = sqlQuery.value(0).toInt();
                c.exp = sqlQuery.value(1).toInt();
                c.card_pass = sqlQuery.value(2).toInt();
                c.card_fail = sqlQuery.value(3).toInt();
                c.word_eliminate = sqlQuery.value(4).toInt();
            } else {
                throw sqlQuery.lastError();
            }
        } else {
            throw sqlQuery.lastError();
        }
        return c;
    }

    /**
     * @brief 更新出题人信息
     *
     * @param wb 出题人信息
     */
    void updateUser(const WordBuilder &wb) {
        if (wb.exp < 0) {
            throw "exp overflow";
        }
        QString query = QString("UPDATE WordBuilder"
                                " SET level='%1', exp='%2', build_word='%3'"
                                " WHERE user_login = '%4';")
                            .arg(wb.level)
                            .arg(wb.exp)
                            .arg(wb.build_word)
                            .arg(QString::fromStdString(wb.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if (!sqlQuery.exec()) {
            throw sqlQuery.lastError();
        }
    }

    /**
     * @brief 更新玩家信息
     *
     * @param 玩家信息
     */
    void updateUser(const Challenger &c) {
        if (c.exp < 0) {
            throw "exp overthrow";
        }
        QString query = QString("UPDATE Challenger"
                                " SET level='%1', exp='%2', card_pass='%3', "
                                "card_fail='%4', word_eliminate='%5'"
                                " WHERE user_login='%6';")
                            .arg(c.level)
                            .arg(c.exp)
                            .arg(c.card_pass)
                            .arg(c.card_fail)
                            .arg(c.word_eliminate)
                            .arg(QString::fromStdString(c.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if (!sqlQuery.exec()) {
            throw sqlQuery.lastError();
        }
    }

    /**
     * @brief getSearchWordBuilderMakeTable
     * @param model sql模型
     * @param former 搜索的类型
     * @param latter 搜索的值
     */
    void getSearchWordBuilderMakeTable(QVector<QVector<QString>> &model,
                                       std::string former, std::string latter) {
        QString query = QString("SELECT user_login, level, exp, build_word "
                                "FROM WordBuilder where %1='%2';")
                            .arg(QString::fromStdString(former))
                            .arg(QString::fromStdString(latter));
        QSqlQuery qry;
        qry.prepare(query);
        if (qry.exec()) {
            while (qry.next()) {
                QVector<QString> tmp;
                tmp.push_back(qry.value(0).toString());
                tmp.push_back(qry.value(1).toString());
                tmp.push_back(qry.value(2).toString());
                tmp.push_back(qry.value(3).toString());
                model.push_back(tmp);
            }
        }
    }


    /**
     * @brief getSearchChallengerMakeTable
     * @param model sql模型
     * @param former 搜索的类型
     * @param latter 搜索的值
     */
    void getSearchChallengerMakeTable(QVector<QVector<QString>> &model,
                                      std::string former, std::string latter) {
        QString query =
            QString("SELECT user_login, level, exp, card_pass, word_eliminate "
                    "FROM Challenger where %1='%2';")
                .arg(QString::fromStdString(former))
                .arg(QString::fromStdString(latter));
        QSqlQuery qry;
        qry.prepare(query);
        if (qry.exec()) {
            while (qry.next()) {
                QVector<QString> tmp;
                tmp.push_back(qry.value(0).toString());
                tmp.push_back(qry.value(1).toString());
                tmp.push_back(qry.value(2).toString());
                tmp.push_back(qry.value(3).toString());
                tmp.push_back(qry.value(4).toString());
                model.push_back(tmp);
            }
        }
    }
};

#endif // LOGIN_H
