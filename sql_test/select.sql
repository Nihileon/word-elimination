-- WordBuilder
SELECT COUNT(*) FROM WordBuilder WHERE user_login=?

SELECT user_pass, level, exp, build_word, word_pass, word_fail
    FROM WordBuilder WHERE user_login=?

-- Challenger
SELECT COUNT(*) FROM Challenger WHERE user_login=?

SELECT user_pass, level, exp, card_pass, card_fail, word_eliminate
    FROM Challenger WHERE user_login=?

--word
SELECT word, builder, fail_time, pass_time
    FROM Word WHERE len= ?
        ORDER BY RANDOM() LIMIT 1;

SELECT COUNT(*) FROM Word WHERE builder=?

