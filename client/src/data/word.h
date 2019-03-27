#ifndef WORD_H
#define WORD_H
#include "basic.h"
#include <sqlite_modern_cpp.h>

class Word{
private:
    sqlite::database db;
    static Word *_instance;
    Word(const string path = "test.db"):db(path.c_str()){}
    ~Word();
public:
    static auto instance();
    static void destroy();

    void insert(const WordInfo &wi){
        db << "INSERT INTO Word (word,builder,len) VALUES (?,?,?);"
           << wi.word << wi.builder << wi.len;
    }

    auto getWord(int len){
        WordInfo wi;
        db << "SELECT word, builder, fail_time, pass_time"
              "FROM Word WHERE len=?"
              "ORDER BY RANDOM() LIMIT 1"
           << len
           >> [&](string word, string builder, int fail_time, int pass_time){
            wi.word = word;
            wi.builder = builder;
            wi.fail_time = fail_time;
            wi.pass_time = pass_time;
        };
        return wi;
    }
};

Word* Word::_instance = nullptr;

auto Word::instance(){
    if(_instance == nullptr){
        _instance = new Word();
    }
    return _instance;
}

void Word::destroy(){
    if(_instance != nullptr){
        delete _instance;
    }
    return;
}


#endif // WORD_H
