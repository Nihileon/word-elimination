#include "gamedialog.h"
#include "ui/GameDialog_ui.h"



GameDialog::GameDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::GameDialogUi),
    qtimer(new QTimer(this))
{
    const int MAX_COUNT_DOWN = 5;

    ui->setupUi(this);
    setWindowTitle(tr("GameBoard"));
    setFixedSize(this->width(), this->height());

    auto wordBrows = ui->wordTextBrowser;
    wordBrows->setFontPointSize(25);
    auto cntBar = ui->countdownProgressBar;
    cntBar->setRange(0, MAX_COUNT_DOWN);
    cntBar->setValue(MAX_COUNT_DOWN);
    auto cntLcd = ui->countdownLcdNumber;
    cntLcd->setDecMode();
    cntLcd->setSegmentStyle(QLCDNumber::Flat);
    cntLcd->display(MAX_COUNT_DOWN);
    auto backPush = ui->backPushBotton;
    connect(backPush, &QPushButton::clicked, this, &GameDialog::showMain);
    connect(qtimer, &QTimer::timeout, this, &GameDialog::countDown);
    auto nextPush = ui->nextPushButton;
    connect(nextPush, &QPushButton::clicked, this, &GameDialog::checkCorrect);

}

void GameDialog::showMain(){
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
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
    }
}

void GameDialog::setChallenger(QVariant data)
{
    this->challenger =  data.value<Challenger>();
}


void GameDialog::gameBegin()
{
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
    const int MAX_COUNT_DOWN = 5;
    wordInfo = Word::instance().getWord(3,10);
    ui->wordTextBrowser->setText(QString::fromStdString(wordInfo.word));
    auto cardBrows = ui->cardTextBrowser;
    std::string s = "Builder: "+wordInfo.builder +
            "\nPass time: " + std::to_string(wordInfo.pass_time)+
            "\nFail time: " +std::to_string(wordInfo.fail_time);
    auto qs = QString::fromStdString(s);
    cardBrows->setText(qs);
    auto cntBar = ui->countdownProgressBar;
    auto cntLcd = ui->countdownLcdNumber;
    cntBar->setValue(MAX_COUNT_DOWN);
    cntLcd->display(MAX_COUNT_DOWN);
    qtimer->start(1000);
}


void GameDialog::checkCorrect(){
    if(wordInfo.word == ui->wordLineEdit->text().toStdString()){
        wordInfo.pass_time++;
        try {
            Delay_MSec_Suspend(50);
            Word::instance().updateWord(wordInfo);
        } catch (sqlite::sqlite_exception &e) {
            std::cout << "check update word" << e.what()<<std::endl;
        }

        challenger.word_eliminate++;
        challenger.exp += 5;
        nextWord();
    }else{
        gameOver();
    }
}

void GameDialog::gameOver(){
    ui->nextPushButton->hide();
    ui->backPushBotton->setDefault(true);
    wordInfo.fail_time++;
    try {
        for(int i=0;i<2;i++){
            Word::instance().updateWord(wordInfo);
            Delay_MSec_Suspend(50);
        }
    } catch (sqlite::sqlite_exception &e) {
        std::cout << " gameover update word"<<e.what()<<std::endl;
    }

    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
    QMessageBox *msg = new QMessageBox;
    msg->setText("Game Over! Please back to the Main window!");
    msg->setWindowModality(Qt::NonModal);
    msg->setStandardButtons(QMessageBox::Close);
    msg->exec();

}


