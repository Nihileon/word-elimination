#ifndef LOGIN_H
#define LOGIN_H
#include "basic.h"
#include <sqlite_modern_cpp.h>
#include <QtSql>
#include <QVariant>
#include <QString>
#include <iostream>

class Login{
private:

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    static Login *_instance;
    //    sqlite::database db;
    //    Login(const string path = "./user.db"):db(path.c_str()){}
    Login(const string path = "/home/nihileon/word-elimination/build-client-Desktop_Qt_5_12_1_GCC_64bit-Debug/src/user.db"){

        db.setDatabaseName(path.c_str());
        if(!db.open()){
            throw db.lastError();
        }

    }
public:
    ~Login(){
        db.close();
    }
    static Login& instance();
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
            //            db<< "INSERT INTO WordBuilder (user_login, user_pass) VALUES (?,?);"
            //              <<li.usr << li.pwd;
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
            //            db<<"INSERT INTO Challenger (user_login, user_pass) VALUES (?,?);"
            //             <<li.usr <<li.pwd;
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
        //        string sqlCheck = "SELECT COUNT(*), user_pass FROM " +userType + " WHERE user_login=?;";
        //        db << sqlCheck.c_str() << loginInfo.usr
        //           >> [&](int is_exist, string user_p ass){
        //            if(is_exist == 1 && user_pass == loginInfo.pwd){
        //                pass_coor = true;
        //            }
        //        };
        //     return pass_coor;
    }

    //    [[deprecated("please use getWordBuilder")]]
    //    auto  _getWordBuilder(const LoginInfo &loginInfo){
    //        WordBuilder wb;
    //        Status status = DEFAULT_STATUS;
    //        int is_exist = 0;
    //        db << "SELECT COUNT(*) FROM WordBuilder WHERE user_login=?;" << loginInfo.usr >> is_exist ;
    //        if(is_exist != 1){
    //            return std::make_pair(USR_NOT_EXIST, wb);
    //        }
    //        wb.usr = loginInfo.usr;
    //        db << "SELECT user_pass, level, exp, build_word, word_pass, word_fail"
    //              " FROM WordBuilder WHERE user_login=?;" << loginInfo.usr
    //           >>[&](string user_pass, int level, int exp, int build_word, int word_pass, int word_fail){
    //            if(loginInfo.pwd != user_pass){
    //                status = PWD_WRONG;
    //            }
    //            wb.level = level;
    //            wb.exp = exp;
    //            wb.build_word = build_word;
    //            wb.word_pass = word_pass;
    //            wb.word_fail = word_fail;
    //        };
    //        return std::make_pair(status, wb);
    //    }

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
            }
        }
        //        db << "SELECT level, exp, build_word, word_pass, word_fail"
        //              " FROM WordBuilder WHERE user_login=?;" << loginInfo.usr
        //           >>[&](int level, int exp, int build_word, int word_pass, int word_fail){
        //            wb.level = level;
        //            wb.exp = exp;
        //            wb.build_word = build_word;
        //            wb.word_pass = word_pass;
        //            wb.word_fail = word_fail;
        //        };
        return wb;
    }

    //    [[deprecated("please use getChallenger")]]
    //    auto _getChallenger(const LoginInfo &loginInfo){
    //        Challenger c;
    //        Status status = DEFAULT_STATUS;
    //        int is_exist = 0;
    //        db << "SELECT COUNT(*) FROM Challenger WHERE user_login=?;" << loginInfo.usr >> is_exist ;
    //        if(is_exist != 1){
    //            return std::make_pair(USR_NOT_EXIST, c);
    //        }
    //        c.usr = loginInfo.usr;
    //        db << "SELECT user_pass, level, exp, card_pass, card_fail, word_eliminate"
    //              " FROM Challenger WHERE user_login=?;"
    //           << loginInfo.usr
    //           >> [&](string user_pass, int level, int exp, int card_pass, int card_fail, int word_eliminate){
    //            if(loginInfo.pwd != user_pass){
    //                status = PWD_WRONG;
    //            }
    //            c.level = level;
    //            c.exp = exp;
    //            c.card_pass = card_pass;
    //            c.card_fail = card_fail;
    //            c.word_eliminate = word_eliminate;
    //        };
    //        return  std::make_pair(status, c);
    //    }

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
            }
        }
        //        db << "SELECT level, exp, card_pass, card_fail, word_eliminate"
        //              " FROM Challenger WHERE user_login=?;"
        //           << loginInfo.usr
        //           >> [&]( int level, int exp, int card_pass, int card_fail, int word_eliminate){
        //            c.level = level;
        //            c.exp = exp;
        //            c.card_pass = card_pass;
        //            c.card_fail = card_fail;
        //            c.word_eliminate = word_eliminate;
        //        };
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
        sqlQuery.exec();
        //        db << "UPDATE WordBuilder"
        //              " SET level=?, exp=?, build_word=?"
        //              " WHERE user_login = ?"
        //           << wb.level << wb.exp << wb.build_word
        //           << wb.usr;
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
        sqlQuery.exec();

        //        db << "UPDATE Challenger"
        //              " SET level=?, exp=?, card_pass=?, card_fail=?,word_eliminate=?"
        //              " WHERE user_login=?"
        //           << c.level << c.exp << c.card_pass << c.card_fail << c.word_eliminate
        //           << c.usr;
    }

    //    auto  getWordBuilderLeader(const string orderType = "exp" ){
    //        db << "SELECT user_login, level, exp, card_pass, word_eliminate"
    //              " FROM Challenger ORDER BY ? desc limit 4;" << orderType
    //           >>[&](int user_login, level, exp, card_pass, word_eliminate)
    //    }
};



#endif // LOGIN_H
