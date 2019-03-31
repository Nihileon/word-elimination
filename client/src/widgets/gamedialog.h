#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>
#include <QMessageBox>
#include "data/word.h"
#include "data/login.h"
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

};

#endif // GAMEDIALOG_H
