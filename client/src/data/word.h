#ifndef WORD_H
#define WORD_H
#include "basic.h"
#include <sqlite_modern_cpp.h>
#include <fstream>

class Word{
private:
    sqlite::database db;
    static Word *_instance;
    Word(const string path = "word.db"):db(path.c_str()){}

public:
    static Word& instance();
    static void destroy();

    void insert(const WordInfo &wi){
        db << "INSERT INTO Word (word,builder,len) VALUES (?,?,?); "
           << wi.word << wi.builder << wi.len;
    }

    auto getWord(int min, int max){
        WordInfo wi;
        db << "SELECT word, builder, fail_time, pass_time "
              "FROM Word WHERE (len>=? and len<=?) "
              "ORDER BY RANDOM() LIMIT 1; "
           << min << max
           >> [&](string word, string builder, int fail_time, int pass_time){
            wi.word = word;
            wi.builder = builder;
            wi.fail_time = fail_time;
            wi.pass_time = pass_time;
        };
        return wi;
    }

    void updateWord(WordInfo &wordInfo){
        db << "UPDATE Word "
              "SET fail_time=?, pass_time=? "
              "WHERE word=?; "
           << wordInfo.fail_time << wordInfo.pass_time << wordInfo.word;
    }

    void _initWord(){
        using namespace std;
        using namespace sqlite;
        fstream fp;
        fp.open("./COCA_20000.txt", ios::in);
        int count[35] = {0};
        string s;
        for(;!fp.eof();){
            fp>>s;
            if(s.length()>3){
                if(count[s.length()]++ < 35){
                    try{
                        db << "INSERT INTO Word (word,len) VALUES (?,?); "
                           << s << s.length();
                    }catch(sqlite_exception &e){}
                }
            }
        }

    }
};

#endif // WORD_H
