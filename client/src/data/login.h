#ifndef LOGIN_H
#define LOGIN_H
#include "basic.h"
#include <sqlite_modern_cpp.h>

class Login{
private:
    sqlite::database db;
    static Login *_instance;

    Login(const string path = "./test.db"):db(path.c_str()){}
 public:
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
            db<< "INSERT INTO WordBuilder (user_login, user_pass) VALUES (?,?);"
              <<li.usr << li.pwd;
            break;
        }
        case LoginInfo::CHALLENGER:{
            db<<"INSERT INTO Challenger (user_login, user_pass) VALUES (?,?);"
             <<li.usr <<li.pwd;
            break;
        }
        }
    }

    auto getWordBuilder(const LoginInfo &loginInfo){
        WordBuilder wb;
        Status status = DEFAULT_STATUS;
        int is_exist = 0;
        db << "SELECT COUNT(*) FROM WordBuilder WHERE user_login=?;" << loginInfo.usr >> is_exist ;
        if(is_exist != 1){
            return std::make_pair(USR_NOT_EXIST, wb);
        }
        wb.usr = loginInfo.usr;
        db << "SELECT user_pass level, exp, build_word, word_pass, word_fail"
           " FROM WordBuilder WHERE user_login=?;" << loginInfo.usr
           >>[&](string user_pass, int level, int exp, int build_word, int word_pass, int word_fail){
            if(loginInfo.pwd != user_pass){
                status = PWD_WRONG;
            }
            wb.level = level;
            wb.exp = exp;
            wb.build_word = build_word;
            wb.word_pass = word_pass;
            wb.word_fail = word_fail;
        };
        return std::make_pair(status, wb);
    }

    auto getChallenger(const LoginInfo &loginInfo){
        Challenger c;
        Status status = DEFAULT_STATUS;
        int is_exist = 0;
        db << "SELECT COUNT(*) FROM Challenger WHERE user_login=?;" << loginInfo.usr >> is_exist ;
        if(is_exist != 1){
            return std::make_pair(USR_NOT_EXIST, c);
        }
        c.usr = loginInfo.usr;
        db << "SELECT user_pass, level, exp, card_pass, card_fail, word_eliminate"
           " FROM Challenger WHERE user_login=?;"
           << loginInfo.usr
           >> [&](string user_pass, int level, int exp, int card_pass, int card_fail, int word_eliminate){
            if(loginInfo.pwd != user_pass){
                status = PWD_WRONG;
            }
            c.level = level;
            c.exp = exp;
            c.card_pass = card_pass;
            c.card_fail = card_fail;
            c.word_eliminate = word_eliminate;
        };
        return  std::make_pair(status, c);
    }

    void updateUser(const WordBuilder &wb){
        db << "UPDATE WordBuilder"
           " SET level=?, exp=?, build_word=?"
           " WHERE user_login = ?"
           << wb.level << wb.exp << wb.build_word
           << wb.usr;
    }

    void updateUser(const Challenger &c){
        db << "UPDATE Challenger"
           " SET level=?, exp=?, card_pass=?, card_fail=?,word_eliminate=?"
           " WHERE user_login=?"
           << c.level << c.exp << c.card_pass << c.card_fail << c.word_eliminate
           << c.usr;
    }
};



#endif // LOGIN_H
