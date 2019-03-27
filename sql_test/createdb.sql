CREATE TABLE Challenger
(
    ID INTEGER PRIMARY KEY,
    user_login VARCHAR(20) NOT NULL,
    user_pass VARCHAR(300) NOT NULL,
    pass_salt VARCHAR(129) DEFAULT '0',
    nick_name VARCHAR ,
    play_time VARCHAR(25) DEFAULT 0,
    register_time VARCHAR(25) DEFAULT 0,
    level INT(11) DEFAULT 1,
    exp INT(11) DEFAULT 0,
    card_pass INT(11) DEFAULT 0,
    card_fail INT(11) DEFAULT 0,
    word_eliminate INT(11) DEFAULT 0,
    UNIQUE(user_login)
);

CREATE TABLE WordBuilder
(
    ID INTEGER PRIMARY KEY,
    user_login VARCHAR(20) NOT NULL,
    user_pass VARCHAR(300) NOT NULL,
    pass_salt VARCHAR(129) DEFAULT '0',
    nick_name VARCHAR,
    register_time VARCHAR(25) DEFAULT 0,
    level INT(11) DEFAULT 1,
    exp INT(11) DEFAULT 0,
    build_word INT(11) DEFAULT 0,
    word_pass INT(11) DEFAULT 0,
    word_fail INT(11) DEFAULT 0,
    UNIQUE(user_login)
);

CREATE TABLE Word(
    ID INTEGER PRIMARY KEY,
    word VARCHAR NOT NULL,
    builder VARCHAR DEFAULT "admin",
    fail_time INT(11) DEFAULT 0,
    pass_time INT(11) DEFAULT 0,
    len INT(11) NOT NULL,
    UNIQUE(word)
);