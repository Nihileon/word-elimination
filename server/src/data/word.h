#ifndef WORD_H
#define WORD_H

#include "basic.h"
#include <QtSql>
#include <fstream>

/**
 * @brief 单词信息类
 *
 */
class Word
{
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
    Word(const string path = "./word.db")
    {
        if (QSqlDatabase::contains("words_connection"))
            db = QSqlDatabase::database("words_connection");
        else
            db = QSqlDatabase::addDatabase("QSQLITE", "words_onnection");
        db.setDatabaseName(path.c_str());
        if (!db.open()) {
            throw db.lastError();
        }
    }

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
    void insert(const WordInfo &wi)
    {
        auto query =
            QString(
                "INSERT INTO Word (word,builder,len) VALUES ('%1','%2','%3');")
                .arg(QString::fromStdString(wi.word))
                .arg(QString::fromStdString(wi.builder))
                .arg(QString::fromStdString(std::to_string(wi.len)));
        QSqlQuery sqlQuery("words_connection", db);
        sqlQuery.prepare(query);
        if (!sqlQuery.exec()) {
            throw sqlQuery.lastError();
        }
        //        db << "INSERT INTO Word (word,builder,len) VALUES (?,?,?); "
        //           << wi.word << wi.builder << wi.len;
    }

    /**
     * @brief Get the Word object
     *
     * @param min 最小长度
     * @param max 最大长度
     * @return auto 单词信息
     */
    auto getWord(int min, int max)
    {
        WordInfo wi;
        QString query = QString("SELECT word, builder, fail_time, pass_time, len "
                                "FROM Word WHERE (len>='%1' and len<=%2) "
                                "ORDER BY RANDOM() LIMIT 1; ")
                            .arg(QString::number(min))
                            .arg(QString::number(max));
        QSqlQuery sqlQuery("words_connection", db);
        sqlQuery.prepare(query);
        if (sqlQuery.exec()) {
            if (sqlQuery.next()) {
                wi.word = sqlQuery.value(0).toString().toStdString();
                wi.builder = sqlQuery.value(1).toString().toStdString();
                wi.fail_time = sqlQuery.value(2).toInt();
                wi.pass_time = sqlQuery.value(3).toInt();
                wi.len = sqlQuery.value(4).toInt();
            }
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
        QString query = QString("SELECT word,fail_time,pass_time "
                                "FROM Word WHERE builder='%1' ORDER BY ID;")
                            .arg(QString::fromStdString(username));
        QSqlQuery qry("words_connection", db);
        qry.prepare(query);
        if (qry.exec()) {
            while (qry.next()) {
                QVector<QString> line;
                line.push_back(qry.value(0).toString());
                line.push_back(qry.value(1).toString());
                line.push_back(qry.value(2).toString());
                model.push_back(line);
            }

        }
    }

    /**
     * @brief 更新数据库的单词信息
     *
     * @param wordInfo 单词信息
     */
    void updateWord(WordInfo &wordInfo)
    {
        QString query = QString("UPDATE Word "
                                "SET fail_time='%1', pass_time='%2' "
                                "WHERE word='%3';")
                            .arg(wordInfo.fail_time)
                            .arg(wordInfo.pass_time)
                            .arg(QString(wordInfo.word.c_str()));
        QSqlQuery sqlQuery("words_connection", db);
        sqlQuery.prepare(query);
        if (!sqlQuery.exec()) {
            throw sqlQuery.lastError();
        }
    }

    /**
     * @brief 初始化单词, 仅在未建立数据库时使用
     *
     */
    void _initWord()
    {
        using namespace std;
        fstream fp;
        fp.open("./COCA_20000.txt", ios::in);
        int count[35] = {0};
        string s;
        for (; !fp.eof();) {
            fp >> s;
            if (s.length() > 3) {
                if (count[s.length()]++ < 35) {
                    try {
                        auto query = QString("INSERT INTO Word (word,len) "
                                             "VALUES ('%1','%2');")
                                         .arg(QString::fromStdString(s))
                                         .arg(QString::number(s.length()));
                        QSqlQuery sqlQuery("words_connection", db);
                        sqlQuery.prepare(query);
                        sqlQuery.exec();
                    } catch (QSqlError &e) {
                        // 插入过慢出现的错误可以忽略
                    }
                }
            }
        }
    }
};

#endif // WORD_H
