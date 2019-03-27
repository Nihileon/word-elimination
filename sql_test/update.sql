UPDATE Challenger
    SET level=?, exp=?, card_pass=?, card_fail=?,word_eliminate=?
        WHERE user_login=?

UPDATE WordBuilder
    SET level=?, exp=?, build_word=?
        WHERE user_login = ?

UPDATE Word
    SET fail_time=?, pass_time=?
        WHERE word=?

