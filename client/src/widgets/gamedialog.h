#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>
#include <QMessageBox>
#include <cmath>
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
    void showMain();
    void init();
    void gameOver();
    //when pass k words, go to the next card
    void nextCard();
    //when input the correct word, the player can get the next word
    void nextWord();
    //count down, update the time, and hide the word when timeout;
    void countBegin();
    void checkCorrect();
    void setGameOver();
    void setLevel();
    void Delay_MSec_Suspend(int msec)
    {
        QTime _Timer = QTime::currentTime();

        QTime _NowTimer;
        do{
            _NowTimer=QTime::currentTime();
        }while (_Timer.msecsTo(_NowTimer)<=msec);

    }
signals:
    void toMain();
    void toNextWord();
    void sendChallenger(QVariant data);

public slots:
    void gameBegin();
    void countDown();
    void setChallenger(QVariant data);


private:
    Challenger challenger;
    Ui::GameDialogUi *ui;
    QTimer* qtimer;
    int counter;
    WordInfo wordInfo;
    int wordLen = 5;
    struct CardInfo{
        int cardPassWordNum;
        int wordDisplayTime;
        int exp;
    };
    CardInfo cardInfo;
    int card  = 1;
    CardInfo getCardPassInfo(int card){
        CardInfo ci;
        auto passWordNum = [&](int card){double temp=1.2; for(int i=1;i<card;i++) temp*=1.2; return static_cast<int>(temp);};
        ci.cardPassWordNum = passWordNum(card);
        auto time = [&](int card){
            if(card < 3) return 5;
            else if(card<6) return 4;
            else if(card<9) return 3;
            else if(card<11) return 2;
            else return 1;};
        ci.wordDisplayTime = time(card);
        auto exp = [&](int card){double temp=1.7; for(int i=1;i<card;i++) temp*=1.7; return static_cast<int>(temp);};
        ci.exp = exp(card);
        return ci;
    }

};

#endif // GAMEDIALOG_H
