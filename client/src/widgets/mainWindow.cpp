#include "widgets/mainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/registerdialog.h"
#include "widgets/LoginDialog.h"
#include "widgets/LeaderBoardDialog.h"
#include <QObject>
#include <QDesktopWidget>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    model(new QStandardItemModel)
{
    initWindow();
    setFixedSize(this->width(), this->height());
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width()- this->width())/2, (desktop->height() - this->height())/2);

    ui->personalInfoTableView->setStyleSheet("QTableCornerButton::section{border: none;background:white;}"
                                             "QHeaderView{ border: none; background:white; }"
                                             "border: none;background:white;"
                                             );
    ui->personalInfoTableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                                 " border: none;background-color:#ffffff;}");
    ui->personalInfoTableView->verticalHeader()->setStyleSheet("QHeaderView::section {"
                                                               " border: none;background-color:#ffffff;}");
    ui->personalInfoTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->personalInfoTableView->verticalHeader()->hide();
    ui->personalInfoTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->personalInfoTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->personalInfoTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->personalInfoTableView->setUpdatesEnabled(true);
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
    //    initWindow();
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
    model->item(1,1)->setText(QString::number(wordBuilder.level));
    //    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.level))));
    model->item(2,1)->setText(QString::number(wordBuilder.exp));
    //    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.exp))));
    model->item(3,1)->setText(QString::number(wordBuilder.build_word));
    //    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.build_word))));
}

void MainWindow::refreshChallengerWindow()
{
    using std::to_string;
    model->item(1,1)->setText(QString::number(challenger.level));
    //    model->setItem(1,1,new QStandardItem(QString::fromStdString(to_string(challenger.level))));
    model->item(2,1)->setText(QString::number(challenger.exp));
    //    model->setItem(2,1,new QStandardItem(QString::fromStdString(to_string(challenger.exp))));
    model->item(3,1)->setText(QString::number(challenger.card_pass));
    //    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(challenger.card_pass))));
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


    } catch (QSqlError &e) {
        std::cout << "set Challenger:" << e.text().toStdString()<<std::endl;
    }

}

void MainWindow::setWordBuilder(QVariant data)
{
    this->wordBuilder = data.value<WordBuilder>();
    refreshWordBuilderWindow();
    try {
        Delay_MSec_Suspend(50);
        Login::instance().updateUser(this->wordBuilder);
    } catch (QSqlError &e) {
        std::cout << "set WordBuilder:" << e.text().toStdString()<<std::endl;
    }

}

void MainWindow::closeAll()
{
    emit sendCloseAll();
}

void MainWindow::initWindow(){
    //    QStringList labels = QObject::trUtf8("频率,功率,误差").simplified().split(",");
    //    QStringList labels = QObject::trUtf8("personal info,value").split(",");
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("Info"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("Value"));
    //        model->item(0,0)->setForeground(QBrush(QColor(255, 0, 0)));
    //        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
    auto personalTable = ui->personalInfoTableView;
    personalTable->setModel(model);
    personalTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    //    personalTable->setSortingEnabled(true);


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
    model->setItem(3,0, new QStandardItem("num of build"));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(wordBuilder.build_word))));
    QFont ft;
    ft.setPointSize(14);
    for(int i=0;i<4;i++){
        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,1) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,0)->setFont(ft);
        model->item(i,1)->setFont(ft);
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
    model->setItem(3,0, new QStandardItem("max card"));
    model->setItem(3,1,new QStandardItem(QString::fromStdString(to_string(challenger.card_pass))));
    QFont ft;
    ft.setPointSize(14);
    for(int i=0;i<4;i++){

        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,1) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,0)->setFont(ft);
        model->item(i,1)->setFont(ft);
    }
    ui->buildWordPushButton->hide();
    ui->gamePushButton->setDefault(true);
    ui->gamePushButton->setShortcut(Qt::Key_Enter);
}

