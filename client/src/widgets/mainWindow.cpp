#include "widgets/mainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/registerdialog.h"
#include "widgets/LoginDialog.h"
#include "widgets/LeaderBoardDialog.h"
#include <QObject>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
      model(new QStandardItemModel)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    connect(ui->gamePushButton, &QPushButton::clicked, this, &MainWindow::showGame);
    connect(ui->buildWordPushButton, &QPushButton::clicked, this, &MainWindow::showBuildWord);
    connect(ui->logoutPushBotton, &QPushButton::clicked, this, &MainWindow::closeAll);
    connect(ui->leaderboardPushBotton, &QPushButton::clicked, this, &MainWindow::showLeaderboard);
}

MainWindow::~MainWindow(){
    delete ui;
    delete model;
}

void MainWindow::setUser(QVariant data){
    initWindow();
    loginInfo = data.value<LoginInfo>();
    if(loginInfo.type == LoginInfo::WORD_BUILDER){
        wordBuilder = Login::instance().getWordBuilder(loginInfo);
        initWordBuilderWindow();
    }else if(loginInfo.type == LoginInfo::CHALLENGER){
        challenger = Login::instance().getChallenger(loginInfo);
        initChallengerWindow();
    }
}

void MainWindow::refreshWordBuilderWindow()
{
    using std::to_string;
    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.level))));
    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.exp))));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.build_word))));
}

void MainWindow::refreshChallengerWindow()
{
    using std::to_string;
    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(challenger.level))));
    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(challenger.exp))));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(challenger.card_pass))));
}

void MainWindow::showGame(){
    this->hide();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
    emit toGame();
}

void MainWindow::showBuildWord(){
    this->hide();
    QVariant data;
    data.setValue(wordBuilder);
    emit sendWordBuilder(data);
    emit toBuildWord();
}

void MainWindow::showLeaderboard()
{
    this->hide();
    emit toLeader();
}

void MainWindow::setChallenger(QVariant data)
{
    this->challenger = data.value<Challenger>();
    refreshChallengerWindow();
    try {
        Delay_MSec_Suspend(50);
        Login::instance().updateUser(this->challenger);


    } catch (sqlite::sqlite_exception &e) {
        std::cout << "set Challenger:" << e.what()<<std::endl;
    }

}

void MainWindow::setWordBuilder(QVariant data)
{
    this->wordBuilder = data.value<WordBuilder>();
    refreshWordBuilderWindow();
    try {
        Delay_MSec_Suspend(50);
        Login::instance().updateUser(this->wordBuilder);
    } catch (sqlite::sqlite_exception &e) {
        std::cout << "set WordBuilder:" << e.what()<<std::endl;
    }

}

void MainWindow::closeAll()
{
    emit sendCloseAll();
}

void MainWindow::initWindow(){
    //    QStringList labels = QObject::trUtf8("频率,功率,误差").simplified().split(",");
    //    QStringList labels = QObject::trUtf8("personal info,value").split(",");
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("Info"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("Value"));
//        model->item(0,0)->setForeground(QBrush(QColor(255, 0, 0)));
//        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        auto personalTable = ui->personalInfoTableView;
    personalTable->setModel(model);
    personalTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    personalTable->setSortingEnabled(true);


}

void MainWindow::initWordBuilderWindow()
{
    using std::to_string;

    model->setItem(0,0,new QStandardItem("Username"));
    model->setItem(0,1,new QStandardItem(QString::fromStdString(wordBuilder.usr)));
    //level, exp, build_word
    model->setItem(1,0, new QStandardItem("level"));
    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.level))));
    model->setItem(2,0, new QStandardItem("exp"));
    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.exp))));
    model->setItem(3,0, new QStandardItem("word build num"));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.build_word))));
    for(int i=0;i<4;i++){
        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,1) ->setTextAlignment(Qt::AlignCenter);
    }
    ui->gamePushButton->hide();
    ui->buildWordPushButton->setDefault(true);
    ui->buildWordPushButton->setShortcut(Qt::Key_Enter);



}

void MainWindow::initChallengerWindow()
{
    using std::to_string;

    model->setItem(0,0,new QStandardItem("Username"));
    model->setItem(0,1,new QStandardItem(QString::fromStdString(challenger.usr)));
    //level, exp, card_pass, card_fail, word_eliminate
    model->setItem(1,0, new QStandardItem("level"));
    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(challenger.level))));
    model->setItem(2,0, new QStandardItem("exp"));
    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(challenger.exp))));
    model->setItem(3,0, new QStandardItem("card pass max"));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(challenger.card_pass))));
    for(int i=0;i<4;i++){
        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,1) ->setTextAlignment(Qt::AlignCenter);
    }
    ui->buildWordPushButton->hide();
    ui->gamePushButton->setDefault(true);
    ui->gamePushButton->setShortcut(Qt::Key_Enter);
}

