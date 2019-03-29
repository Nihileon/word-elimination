#include "gamedialog.h"
#include "ui/GameDialog_ui.h"

GameDialog::GameDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::GameDialogUi){
    ui->setupUi(this);
    setWindowTitle(tr("GameBoard"));
    setFixedSize(this->width(), this->height());
    connect(ui->backPushBotton, &QPushButton::clicked, this, &GameDialog::showMain);
    //    connect(ui->countdownProgressBar, &QProgressBar::valueChanged, &ui->countdownLcdNumber,&QLCDNumber:/)
//    connect(qtimer, &QTimer::timeout, this, &GameDialog::countDown);

    this->init();

}

void GameDialog::showMain(){
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
    else
        qtimer->stop();
}



void GameDialog::init(){
    const int MAX_VALUE = 20;
    ui->wordTextBrowser->setFontPointSize(25);
    ui->wordTextBrowser->setText("word");
    auto cntBar = ui->countdownProgressBar;
    cntBar->setRange(0, MAX_VALUE);
    cntBar->setValue(MAX_VALUE);
    ui->countdownLcdNumber->setDecMode();
    ui->countdownLcdNumber->setSegmentStyle(QLCDNumber::Flat);
    qtimer = new QTimer(this);
    connect(qtimer, &QTimer::timeout, this, &GameDialog::countDown);
    qtimer->start(1000);
    countDown();
}
