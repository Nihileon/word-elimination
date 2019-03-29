#ifndef BASIC_H
#define BASIC_H
#include <string>
#include <QMetaType>
using std::string;


//登陆所需的信息
struct LoginInfo{
    typedef enum{
        WORD_BUILDER,
        CHALLENGER
    }UserType;
    string usr;
    UserType type;
    string pwd;
};

struct User{
    int ID;
    string usr;
    int level;
    int exp;
};

struct WordBuilder : public User{
    int build_word;
    int word_pass;
    int word_fail;
};

struct Challenger : public User{
    int currDiff = 0;
    int card_pass;
    int card_fail;
    int word_eliminate;
};

struct WordInfo{
    int ID;
    string word;
    int user_id;
    string builder;
    int fail_time;
    int pass_time;
    int len;
};

Q_DECLARE_METATYPE(WordBuilder);
Q_DECLARE_METATYPE(Challenger);
Q_DECLARE_METATYPE(WordInfo);
Q_DECLARE_METATYPE(LoginInfo);
#endif // BASIC_H
