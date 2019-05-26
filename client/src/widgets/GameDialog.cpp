/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 19:03:16
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 19:03:16
 */
#include "GameDialog.h"
#include "ui/GameDialog_ui.h"
#include "ui/materialmessagebox.h"
#include <QLabel>
#include <cmath>
#include <qtmaterialdialog.h>

GameDialog::GameDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::GameDialogUi), qtimer(new QTimer(this)),
      msg(new MaterialMessageBox(this)) {
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
    ui->countdownProgressBar->setStyleSheet(
        "border:1px solid "
        "grey;border-radius:2px;text-align:center;background-color:#ffffff;");
    ui->countdownLcdNumber->hide();
    auto wordBrows = ui->wordTextBrowser;
    wordBrows->setFontPointSize(25);
    wordBrows->setAlignment(Qt::AlignCenter);
    auto cntLcd = ui->countdownLcdNumber;
    cntLcd->setDecMode();
    cntLcd->setSegmentStyle(QLCDNumber::Flat);
    cntLcd->display(MAX_COUNT_DOWN);

    connect(ui->backPushBotton, &QPushButton::clicked, this,
            &GameDialog::showMain);
    connect(ui->nextPushButton, &QPushButton::clicked, this,
            &GameDialog::checkCorrect);
    connect(qtimer, &QTimer::timeout, this, &GameDialog::countDown);
    connect(msg->closeButton, &QPushButton::pressed, this,
            &GameDialog::getNextWord);
}

GameDialog::~GameDialog() {
    delete ui;
    delete qtimer;
}

void GameDialog::delayMsecSuspend(int msec) {
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do {
        _NowTimer = QTime::currentTime();
    } while (_Timer.msecsTo(_NowTimer) <= msec);
}

void GameDialog::setCard(int card) { this->card = card; }

int GameDialog::getWordExp() {
    int exp = static_cast<int>(log2(wordInfo.len + 1) *
                               (0.5 * card / (timePerWord + 1)));
    qDebug() << wordInfo.len;
    if (exp < 0)
        throw "getWordExp overflow";
    return exp;
}

void GameDialog::showMain() {
    setLocalChallenger();
    setCard(1);
    this->hide();
    emit toMain();
}

void GameDialog::countDown() {
    auto cntBar = ui->countdownProgressBar;
    auto cntLcd = ui->countdownLcdNumber;
    if (cntBar->value() > 0) {
        cntBar->setValue(cntBar->value() - 1);
        cntLcd->display(cntBar->value());
    } else if (cntBar->value() == 0 && timePerWord == 0) {
        ui->wordTextBrowser->hide();
        ui->wordLineEdit->setDisabled(false);
        ui->wordLineEdit->setFocus();
        timePerWord++;
    } else {
        timePerWord++;
    }
}

void GameDialog::setChallenger(QVariant data) {
    this->challenger = data.value<Challenger>();
}

void GameDialog::gameBegin() {
    setCardInfo();
    this->show();
    ui->nextPushButton->show();
    ui->nextPushButton->setDefault(true);
    ui->nextPushButton->setShortcut(Qt::Key_Enter);
    ui->wordLineEdit->setFocus();
    nextWord(cardInfo.wordLen);
}

void GameDialog::nextWord(int len) {
    qDebug() << "4";
    ui->wordTextBrowser->show();
    ui->wordLineEdit->clear();
    ui->wordLineEdit->setDisabled(true);
    qDebug() << "next word";
    wordInfo = Word::instance().getWord(len - 3, len);
    string tr = "<center><big><font size=14>" + wordInfo.word +
        "</big></font></center>";
    QObject::tr(tr.c_str());
    ui->wordTextBrowser->setText(QObject::tr(tr.c_str()));

    auto cardBrows = ui->cardTextBrowser;
    std::string s = "Card: " + std::to_string(card) +
        "\nWord Builder: " + wordInfo.builder +
        "\nWord Remaining: " + std::to_string(cardInfo.cardPassWordNum);
    cardBrows->setText(QString::fromStdString(s));
    auto cntBar = ui->countdownProgressBar;
    auto cntLcd = ui->countdownLcdNumber;
    cntBar->setValue(cardInfo.wordDisplayTime);
    cntLcd->display(cardInfo.wordDisplayTime);
    timePerWord = 0;
    qtimer->start(1000);
}

void GameDialog::checkCorrect() {
    if (wordInfo.word == ui->wordLineEdit->text().toStdString()) {
        wordInfo.pass_time++;
        delayMsecSuspend(50);
        qDebug() << "check correct";
        Word::instance().updateWord(wordInfo);
        qDebug() << "1";
        challenger.word_eliminate++;
        qDebug() << "2";
        challenger.exp += getWordExp();
        cardInfo.cardPassWordNum--;
        if (cardInfo.cardPassWordNum <= 0) {
            card++;
            challenger.exp += cardInfo.exp;

            setCardInfo();
        }
        qDebug() << "3";
        nextWord(cardInfo.wordLen);
    } else {
        gameOver();
        setCardInfo();
    }
}

void GameDialog::getNextWord() { nextWord(cardInfo.wordLen); }

GameDialog::CardInfo GameDialog::getCardPassInfo(int card) {
    CardInfo ci;

    auto passWordNum = [&](int card) {
        double temp = 1.2;
        for (int i = 1; i < card; i++)
            temp *= 1.2;
        return static_cast<int>(temp);
    };
    ci.cardPassWordNum = passWordNum(card);

    auto time = [&](int card) {
        if (card < 5)
            return 4;
        else if (card < 7)
            return 3;
        else if (card < 10)
            return 2;
        else
            return 1;
    };
    ci.wordDisplayTime = time(card);

    auto length = [&](int card) {
        if (card < 2)
            return 5;
        else if (card < 7)
            return 7;
        else if (card < 13)
            return card;
        else
            return 16;
    };
    ci.wordLen = length(card);

    auto exp = [&](int card) {
        double temp = 1.7;
        for (int i = 1; i < card; i++)
            temp *= 1.7;
        return static_cast<int>(temp);
    };
    ci.exp = exp(card);
    if (ci.exp < 0)
        throw "card exp overflow";
    return ci;
}

void GameDialog::setLevel() {
    challenger.level = static_cast<int>(
        log(static_cast<double>(challenger.exp) + 1) / log(1.3));
}

void GameDialog::setLocalChallenger() {
    if (challenger.card_pass < card - 1) {
        challenger.card_pass = card - 1;
    }
    setLevel();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
}

void GameDialog::gameOver() {
    qtimer->stop();
    wordInfo.fail_time++;
    qDebug() << "game over";
    Word::instance().updateWord(wordInfo);
    setLocalChallenger();
    msg->setText(
        "Game over!\nYou can go back to the menu\nor play this card again.");
    msg->showDialog();
}

void GameDialog::setCardInfo() {
    this->cardInfo = getCardPassInfo(this->card);
    auto cntBar = ui->countdownProgressBar;
    cntBar->setRange(0, cardInfo.wordDisplayTime);
}
