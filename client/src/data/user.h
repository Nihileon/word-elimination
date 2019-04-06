#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <QtSql>
#include <QVariant>
#include <QString>
#include "basic.h"

class User{
private:

    QSqlDatabase db;

    static User *_instance;
    User(const string path = "/home/nihileon/word-elimination/build-client-Desktop_Qt_5_12_1_GCC_64bit-Debug/src/user.db"){
        if (QSqlDatabase::contains("qt_sql_default_connection"))
          db = QSqlDatabase::database("qt_sql_default_connection");
        else
          db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path.c_str());
        if(!db.open()){
            throw db.lastError();
        }

    }
public:
    ~User(){
        db.close();
    }
    static User& instance();
    static void destroy() ;
    typedef enum{
        DEFAULT_STATUS,
        USR_NOT_EXIST,
        PWD_WRONG,
        LOGIN_SUCCESS,
        UNKNOWN
    }Status;

    void insert(const LoginInfo &li){
        switch (li.type) {
        case LoginInfo::WORD_BUILDER:{
            auto query = QString("INSERT INTO WordBuilder (user_login, user_pass) VALUES ( '%1' ,'%2');")\
                    .arg(QString::fromStdString(li.usr))\
                    .arg(QString::fromStdString(li.pwd));
            QSqlQuery sqlQuery;
            sqlQuery.prepare(query);
            if(!sqlQuery.exec()){
                throw sqlQuery.lastError();
            }
            break;
        }
        case LoginInfo::CHALLENGER:{
            auto query = QString("INSERT INTO Challenger (user_login, user_pass) VALUES ('%1','%2');")\
                    .arg(QString::fromStdString(li.usr))\
                    .arg(QString::fromStdString(li.pwd));
            QSqlQuery sqlQuery;
            sqlQuery.prepare(query);
            if(!sqlQuery.exec()){
                throw sqlQuery.lastError();
            }
            break;
        }
        }
    }
    auto isUser(const LoginInfo &loginInfo){
        string userType;
        if(loginInfo.type == LoginInfo::WORD_BUILDER){
            userType = "WordBuilder";
        }else if(loginInfo.type == LoginInfo::CHALLENGER){
            userType = "Challenger";
        }
        QString query = QString("SELECT COUNT(*), user_pass FROM '%1' WHERE user_login='%2';")\
                .arg(QString::fromStdString(userType))\
                .arg(QString::fromStdString(loginInfo.usr));

        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);

        sqlQuery.exec();

            if (sqlQuery.next()) {
                int is_exist = sqlQuery.value(0).toInt();
                string user_pass = sqlQuery.value(1).toString().toStdString();
                if(is_exist == 1 && user_pass == loginInfo.pwd){
                    return true;
                }
            }
        return false;
    }


    auto getWordBuilder(const LoginInfo &loginInfo){
        WordBuilder wb;
        wb.usr = loginInfo.usr;
        QString query = QString("SELECT level, exp, build_word, word_pass, word_fail"
                                " FROM WordBuilder WHERE user_login='%1';")\
                .arg(QString::fromStdString(loginInfo.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if(sqlQuery.exec()){
            if (sqlQuery.next()) {
                wb.level = sqlQuery.value(0).toInt();
                wb.exp = sqlQuery.value(1).toInt();
                wb.build_word = sqlQuery.value(2).toInt();
                wb.word_pass = sqlQuery.value(3).toInt();
                wb.word_fail = sqlQuery.value(4).toInt();
            }else{
                throw sqlQuery.lastError();
            }
        }else{
            throw sqlQuery.lastError();
        }
        return wb;
    }

    void getChallengerMakeTable(QSqlQueryModel* model){
        model->setQuery("SELECT user_pass, level, exp, card_pass, word_eliminate "
                        "FROM Challenger ORDER BY exp DESC;",db);
        model->setHeaderData(0, Qt::Horizontal, "Username");
        model->setHeaderData(1, Qt::Horizontal, "Level");
        model->setHeaderData(2, Qt::Horizontal, "Exp");
        model->setHeaderData(3, Qt::Horizontal, "Max Passed");
//        model->setHeaderData(4, Qt::Horizontal, "Card_fail");
        model->setHeaderData(4, Qt::Horizontal, "Eliminated");

    }

    void getWordBuilderMakeTable(QSqlQueryModel* model){
        model->setQuery("SELECT user_pass, level, exp, build_word "
                        "FROM WordBuilder ORDER BY build_word DESC;");
        model->setHeaderData(0, Qt::Horizontal, "Username");
        model->setHeaderData(1, Qt::Horizontal, "Level");
        model->setHeaderData(2, Qt::Horizontal, "Exp");
        model->setHeaderData(3, Qt::Horizontal, "Word Built");
    }

    auto getChallenger(const LoginInfo &loginInfo){
        Challenger c;
        c.usr = loginInfo.usr;
        QString query = QString("SELECT level, exp, card_pass, card_fail, word_eliminate"
                                " FROM Challenger WHERE user_login='%1';")\
                .arg(QString::fromStdString(loginInfo.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if(sqlQuery.exec()){
            if (sqlQuery.next()) {
                c.level = sqlQuery.value(0).toInt();
                c.exp = sqlQuery.value(1).toInt();
                c.card_pass = sqlQuery.value(2).toInt();
                c.card_fail = sqlQuery.value(3).toInt();
                c.word_eliminate = sqlQuery.value(4).toInt();
            }else{
                throw sqlQuery.lastError();
            }
        }else{
            throw sqlQuery.lastError();
        }
        return c;
    }

    void updateUser(const WordBuilder &wb){
        QString query = QString("UPDATE WordBuilder"
                                " SET level='%1', exp='%2', build_word='%3'"
                                " WHERE user_login = '%4';")\
                .arg(wb.level)\
                .arg(wb.exp)\
                .arg(wb.build_word)\
                .arg(QString::fromStdString(wb.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if(!sqlQuery.exec()){
            throw sqlQuery.lastError();
        }
    }

    void updateUser(const Challenger &c){
        QString query = QString("UPDATE Challenger"
                                " SET level='%1', exp='%2', card_pass='%3', card_fail='%4', word_eliminate='%5'"
                                " WHERE user_login='%6';")\
                .arg(c.level)\
                .arg(c.exp)\
                .arg(c.card_pass)\
                .arg(c.card_fail)
                .arg(c.word_eliminate)
                .arg(QString::fromStdString(c.usr));
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        if(!sqlQuery.exec()){
            throw sqlQuery.lastError();
        }
    }
};



#endif // LOGIN_H
