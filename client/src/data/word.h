#ifndef WORD_H
#define WORD_H

#include "../tcpclient.h"
#include "basicInfo.h"
#include <fstream>

/**
 * @brief 单词信息类
 *
 */
class Word {
private:
    static Word *_instance; /// 单词单实例
    /**
     * @brief 私有化单例构造函数
     *
     * @param path 路径
     */
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
