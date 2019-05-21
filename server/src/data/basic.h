/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 18:11:29
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 20:15:56
 */
#ifndef BASIC_H
#define BASIC_H

#include <QMetaType>
#include <QTime>
#include <string>

using std::string;

/**
 * @brief 登陆所需的信息
 */
struct LoginInfo {
    typedef enum { WORD_BUILDER, CHALLENGER } UserType; /// 用户类型: 出题者和玩家
    string usr; /// 用户名
    UserType type; /// 用户类型
    string pwd; /// 用户密码
};

/**
 * @brief 基本用户信息
 */
struct UserInfo {
    UserInfo() {
        ID = 0;
        usr = "NULL";
    }
    int ID; /// 用户id
    string usr; /// 用户名
    int level; /// 等级
    int exp; /// 经验
};

/**
 * @brief 出题者信息
 *
 */
struct WordBuilder : public UserInfo {
    int build_word; /// 所出的单词数
    int word_pass; // 暂未使用
    int word_fail; // 暂未使用
};

/**
 * @brief 闯关者信息
 *
 */
struct Challenger : public UserInfo {
    int currDiff = 0; // 暂未使用
    int card_pass; /// 通过的关卡
    int card_fail; // 暂未使用
    int word_eliminate; /// 已经消除的单词数
};

/**
 * @brief 单词信息
 *
 */
struct WordInfo {
    int ID; /// 单词ID
    string word; /// 单词全拼
    int user_id; // 暂未使用, 出题人的id
    string builder; /// 出题人的用户名
    int fail_time; /// 该单词的失败次数
    int pass_time; /// 该单词的通过次数
    int len; /// 单词长度
};

/**
 * @brief 为了让数据可以在QVariable中进行传输, 需要用宏声明要传输的变量类型
 *
 */
Q_DECLARE_METATYPE(WordBuilder);
Q_DECLARE_METATYPE(Challenger);
Q_DECLARE_METATYPE(WordInfo);
Q_DECLARE_METATYPE(LoginInfo)
#endif // BASIC_H
