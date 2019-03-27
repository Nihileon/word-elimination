#include <vector>
#include <iostream>
#include <string>

#include "../lib/ormlite.h"
namespace Tables {
    using namespace BOT_ORM;
    using namespace BOT_ORM::Expression;

    using NullString = Nullable<std::string>;
    using NuLLDouble = Nullable<double>;
    using NullInt = Nullable<int>;
    using string = std::string;

    struct User {
        int ID;
        string user_login;
        string user_pass;
        string pass_salt;
        NullString  nick_name;
        string register_time;
        NullInt level;
        NullInt exp;
        //public:
        //    void set_id(const int& id) const:ID(id){}
        //    void set_user_login(const string & userLogin) const:user_login(userLogin){}
        //    void set_user_pass(const string & userPass)const : user_pass(userPass){}
        //    void set_pass_salt(const string & passSalt)const : pass_salt(passSalt){}
        //    void set_nick_name(const NullString& nickName)const : nick_name(nickName){}
        //    void set_level(const int& level)const : level(level){}
    };

    struct  WordBuilder : User {
        NullString play_time;
        NullInt build_word;
        NullInt word_pass;
        NullInt word_fail;
        ORMAP(
            "WordBuilder",
            ID,
            user_login,
            user_pass,
            pass_salt,
            nick_name,
            play_time,
            register_time,
            level,
            exp,
            build_word,
            word_pass);
    };

    struct Challenger :User
    {
        string play_time;
        NullInt card_win;
        NullInt card_fail;
        NullInt word_eliminate;
        ORMAP(
            "Challenger",
            ID,
            user_login,
            user_pass,
            pass_salt,
            nick_name,
            play_time,
            register_time,
            level,
            exp,
            card_win,
            card_fail,
            word_eliminate);
    };

    struct Words
    {
        int ID;
        string word;
        NullInt user_id;
        NullInt fail_time;
        NullInt pass_time;
        NullInt len;
        ORMAP(
            "Words",
            ID,
            word,
            user_id,
            fail_time,
            pass_time,
            len
        )
    };

    ////class [[deprecated("please create table outside")]] Tables
    //class Table
    //{
    //    Challenger challenger;
    //    WordBuilder word_builder;
    //    Words words;
    //public:
    //    //    //´´½¨±í
    //    void create_tables() {
    //        auto field = FieldExtractor{ challenger, word_builder, words };
    //        ORMapper mapper("word_elimination.db");

    //        mapper.CreateTbl(
    //            Challenger{},
    //            Constraint::Default(field(challenger.play_time), string("0")),
    //            Constraint::Default(field(challenger.register_time), string("0")),
    //            Constraint::Default(field(challenger.level), 1),
    //            Constraint::Default(field(challenger.exp), 0),
    //            Constraint::Default(field(challenger.card_win), 0),
    //            Constraint::Default(field(challenger.card_fail), 0),
    //            Constraint::Default(field(challenger.word_eliminate), 0),
    //            Constraint::Unique(field(challenger.user_login))
    //        );
    //    }
    //};




};

using namespace Tables;
int main() {
    //Table tb;
    //tb.create_tables();
}
