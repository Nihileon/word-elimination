#ifndef WORD_H
#define WORD_H
#include "basic.h"
//#include <sqlite_modern_cpp.h>
#include <fstream>
#include <QtSql>

class Word{
private:
    //    sqlite::database db;
    static Word *_instance;
    //    Word(const string path = "word.db"):db(path.c_str()){}
    QSqlDatabase db;
    Word(const string path = "/home/nihileon/word-elimination/build-client-Desktop_Qt_5_12_1_GCC_64bit-Debug/src/word.db"){
        if (QSqlDatabase::contains("words_connection"))
            db = QSqlDatabase::database("words_connection");
        else
            db = QSqlDatabase::addDatabase("QSQLITE", "words_onnection");
        db.setDatabaseName(path.c_str());
        if(!db.open()){
            throw db.lastError();
        }
    }
public:
    static Word& instance();
    static void destroy();

    void insert(const WordInfo &wi){
        auto query = QString("INSERT INTO Word (word,builder,len) VALUES ('%1','%2','%3');")
                .arg(QString::fromStdString(wi.word))
                .arg(QString::fromStdString(wi.builder))
                .arg(QString::fromStdString(std::to_string(wi.len)));
        QSqlQuery sqlQuery("words_connection",db);
        sqlQuery.prepare(query);
        if(!sqlQuery.exec()){
            throw sqlQuery.lastError();
        }
        //        db << "INSERT INTO Word (word,builder,len) VALUES (?,?,?); "
        //           << wi.word << wi.builder << wi.len;
    }

    auto getWord(int min, int max){
        WordInfo wi;
        QString query = QString("SELECT word, builder, fail_time, pass_time "
                                "FROM Word WHERE (len>='%1' and len<=%2) "
                                "ORDER BY RANDOM() LIMIT 1; ")
                .arg(QString::number(min))
                .arg(QString::number(max));
        QSqlQuery sqlQuery("words_connection",db);
        sqlQuery.prepare(query);
        if(sqlQuery.exec()){
            if (sqlQuery.next()) {
                wi.word = sqlQuery.value(0).toString().toStdString();
                wi.builder = sqlQuery.value(1).toString().toStdString();
                wi.fail_time = sqlQuery.value(2).toInt();
                wi.pass_time = sqlQuery.value(3).toInt();
            }
        }
        //        db << "SELECT word, builder, fail_time, pass_time "
        //              "FROM Word WHERE (len>=? and len<=?) "
        //              "ORDER BY RANDOM() LIMIT 1; "
        //           << min << max
        //           >> [&](string word, string builder, int fail_time, int pass_time){
        //            wi.word = word;
        //            wi.builder = builder;
        //            wi.fail_time = fail_time;
        //            wi.pass_time = pass_time;
        //        };
        return wi;
    }

    void updateWord(WordInfo &wordInfo){
        QString query = QString("UPDATE Word "
                                "SET fail_time='%1', pass_time='%2' "
                                "WHERE word='%3';")
                .arg(wordInfo.fail_time)
                .arg( wordInfo.pass_time)
                .arg(QString(wordInfo.word.c_str()));
        QSqlQuery sqlQuery("words_connection",db);
        sqlQuery.prepare(query);
        if(!sqlQuery.exec()){
            throw sqlQuery.lastError();
        }
        //        db << "UPDATE Word "
        //              "SET fail_time=?, pass_time=? "
        //              "WHERE word=?; "
        //           << wordInfo.fail_time << wordInfo.pass_time << wordInfo.word;
    }

    void _initWord(){
        using namespace std;
        fstream fp;
        fp.open("./COCA_20000.txt", ios::in);
        int count[35] = {0};
        string s;
        for(;!fp.eof();){
            fp>>s;
            if(s.length()>3){
                if(count[s.length()]++ < 35){
                    try{
                        auto query = QString("INSERT INTO Word (word,len) VALUES ('%1','%2');")
                                .arg(QString::fromStdString(s))
                                .arg(QString::number(s.length()));
                        QSqlQuery sqlQuery("words_connection",db);
                        sqlQuery.prepare(query);
                        sqlQuery.exec();
                        //                        db << "INSERT INTO Word (word,len) VALUES (?,?); "
                        //                           << s << s.length();
                    }catch(QSqlError &e){}
                }
            }
        }

    }
};

#endif // WORD_H
