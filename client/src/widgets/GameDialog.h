#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <cmath>
#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>
#include <QMessageBox>
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
    void showMain();
    void gameBegin();
    //count down, update the time, and hide the word when timeout;
    void countDown();
    void setChallenger(QVariant data);
    void checkCorrect();

private:
    Ui::GameDialogUi *ui;
    QTimer* qtimer;
    Challenger challenger;
    int counter;
    WordInfo wordInfo;
    int wordLen = 5;
    struct CardInfo{
        int cardPassWordNum;
        int wordDisplayTime;
        int exp;
    }cardInfo;
    int card  = 1;

    CardInfo getCardPassInfo(int card);
    void setLevel();
    void gameOver();
    //when pass k words, go to the next card
    void nextCard();
    //when input the correct word, the player can get the next word
    void nextWord();
    void setGameOver();
    void delayMsecSuspend(int msec);
};

#endif // GAMEDIALOG_H
