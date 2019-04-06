#include <cmath>
#include <QLabel>
#include <qtmaterialdialog.h>
#include "ui/materialmessagebox.h"
#include "ui/GameDialog_ui.h"
#include "GameDialog.h"

GameDialog::GameDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::GameDialogUi),
    qtimer(new QTimer(this)){
    ui->setupUi(this);
    setWindowTitle(tr("GameBoard"));
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    const int MAX_COUNT_DOWN = 5;
    ui->cardTextBrowser->setStyleSheet("border:0px");
    ui->wordTextBrowser->setStyleSheet("border:0px");
    ui->wordLineEdit->setLabel("input what you see.");
    ui->countdownProgressBar->setStyleSheet("border:1px solid grey;border-radius:2px;text-align:center;background-color:#ffffff;");
    ui->countdownLcdNumber->hide();
    auto wordBrows = ui->wordTextBrowser;
    wordBrows->setFontPointSize(25);
    wordBrows->setAlignment(Qt::AlignCenter);
    auto cntLcd = ui->countdownLcdNumber;
    cntLcd->setDecMode();
    cntLcd->setSegmentStyle(QLCDNumber::Flat);
    cntLcd->display(MAX_COUNT_DOWN);

    connect(ui->backPushBotton, &QPushButton::clicked, this, &GameDialog::showMain);
    connect(ui->nextPushButton, &QPushButton::clicked, this, &GameDialog::checkCorrect);
    connect(qtimer, &QTimer::timeout, this, &GameDialog::countDown);
}

GameDialog::~GameDialog(){
    delete  ui;
    delete qtimer;
}

void GameDialog::delayMsecSuspend(int msec){
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do{
        _NowTimer=QTime::currentTime();
    }while (_Timer.msecsTo(_NowTimer)<=msec);
}

void GameDialog::showMain(){
    setGameOver();
    this->hide();
    emit toMain();
}

void GameDialog::countDown(){
    auto cntBar = ui->countdownProgressBar;
    auto cntLcd = ui->countdownLcdNumber;
    if(cntBar->value() >0){
        cntBar->setValue(cntBar->value()-1);
        cntLcd->display(cntBar->value());
    }
    if(cntBar->value() == 0){
        qtimer->stop();
        ui->wordTextBrowser->hide();
        ui->wordLineEdit->setDisabled(false);
        ui->wordLineEdit->setFocus();
    }
}

void GameDialog::setChallenger(QVariant data){
    this->challenger =  data.value<Challenger>();
}

void GameDialog::gameBegin(){
    nextCard();
    this->show();
    ui->nextPushButton->show();
    ui->nextPushButton->setDefault(true);
    ui->nextPushButton->setShortcut(Qt::Key_Enter);
    ui->wordLineEdit->setFocus();
    nextWord();
}

void GameDialog::nextWord(){
    ui->wordTextBrowser->show();
    ui->wordLineEdit->clear();
    ui->wordLineEdit->setDisabled(true);

    wordInfo = Word::instance().getWord(3,10);
    string tr = "<center><big><font size=14>"+wordInfo.word+"</big></font></center>";
    QObject::tr(tr.c_str());
    ui->wordTextBrowser->setText(QObject::tr(tr.c_str()));

    auto cardBrows = ui->cardTextBrowser;
    std::string s = "Card: " + std::to_string(card)+
            "\t\t\tWord Builder: "+wordInfo.builder +
            "\nPass time: " + std::to_string(wordInfo.pass_time)+
            "\t\tFail time: " +std::to_string(wordInfo.fail_time);
    auto qs = QString::fromStdString(s);
    cardBrows->setText(qs);
    auto cntBar = ui->countdownProgressBar;
    auto cntLcd = ui->countdownLcdNumber;
    cntBar->setValue(cardInfo.wordDisplayTime);
    cntLcd->display(cardInfo.wordDisplayTime);
    qtimer->start(1000);
}

void GameDialog::checkCorrect(){
    if(wordInfo.word == ui->wordLineEdit->text().toStdString()){
        wordInfo.pass_time++;
        try {
            delayMsecSuspend(50);
            Word::instance().updateWord(wordInfo);
        } catch (QSqlError &e) {
            std::cout << "check update word" << e.text().toStdString()<<std::endl;
        }
        challenger.word_eliminate++;
        cardInfo.cardPassWordNum--;
        if(cardInfo.cardPassWordNum <= 0){
            card++;
            challenger.exp += cardInfo.exp;
            nextCard();
        }
        nextWord();
    }else{
        gameOver();
    }
}

GameDialog::CardInfo GameDialog::getCardPassInfo(int card){
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

void GameDialog::setLevel(){
    challenger.level = static_cast<int>(log(static_cast<double>(challenger.exp)) / log(1.3));
}

void GameDialog::setGameOver(){
    if(challenger.card_pass < card-1){
        challenger.card_pass = card-1;
    }
    card = 1;
    setLevel();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
}

void GameDialog::gameOver(){
    ui->nextPushButton->hide();
    ui->nextPushButton->setDefault(false);
    wordInfo.fail_time++;
    try {
        for(int i=0;i<2;i++){
            Word::instance().updateWord(wordInfo);
            delayMsecSuspend(50);
        }
    } catch (QSqlError &e) {
        std::cout << " gameover update word"<<e.text().toStdString()<<std::endl;
    }
    setGameOver();
    MaterialMessageBox *msg = new MaterialMessageBox(this);
    msg->setText("Game over! Please go back to the menu.");
    msg->show();
}

void GameDialog::nextCard(){
    this->cardInfo =  getCardPassInfo(this->card);
    auto cntBar = ui->countdownProgressBar;
    cntBar->setRange(0, cardInfo.wordDisplayTime);
}

