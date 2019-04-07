#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <cmath>
#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>
#include <QMessageBox>
#include <materialmessagebox.h>
#include "data/word.h"
#include "data/user.h"

namespace Ui {
class GameDialogUi;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget* parent = nullptr);
    ~GameDialog();

signals:
    void toMain();
    void toNextWord();
    void sendChallenger(QVariant data);

public slots:
    void gameBegin();
    void setChallenger(QVariant data);

private slots:
    void showMain();
    //count down, update the time, and hide the word when timeout;
    void countDown();
    void checkCorrect();
    void getNextWord();

private:
    Ui::GameDialogUi *ui;
    QTimer* qtimer;
    MaterialMessageBox *msg;
    Challenger challenger;
    int counter;
    WordInfo wordInfo;
    int wordLen = 5;
    struct CardInfo{
        int cardPassWordNum;
        int wordDisplayTime;
        int exp;
        // word length from wordLen-3 to wordLen
        int wordLen;
    }cardInfo;
    int card  = 1;
    int timePerWord = 0;

    CardInfo getCardPassInfo(int card);
    void setLevel();
    void setLocalChallenger();
    //when pass k words, go to the next card
    void setCardInfo();
    //when input the correct word, the player can get the next word
    void nextWord(int len=5);
    //fail in this card and replay
    void cardFail();
    void gameOver();
    void delayMsecSuspend(int msec);
    void setCard(int card);
    int getWordExp();
};

#endif // GAMEDIALOG_H
