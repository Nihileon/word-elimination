/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:38
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:38
 */
#include "widgets/MainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/LeaderBoardDialog.h"
#include "widgets/LoginDialog.h"
#include "widgets/RegisterDialog.h"
#include <QDesktopWidget>
#include <QObject>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      model(new QStandardItemModel), msg(new MaterialMessageBox(this)) {
    initWindow();

    connect(ui->gamePushButton, &QPushButton::clicked, [&]() {
        if (ui->singleModeRadioButton->isChecked()) {
            showSingleGame();
        } else {
            showDoubleGame();
        }
    });
    connect(ui->buildWordPushButton, &QPushButton::clicked, this,
            &MainWindow::showBuildWord);
    connect(ui->logoutPushBotton, &QPushButton::clicked, this,
            &MainWindow::closeAll);
    connect(ui->leaderboardPushBotton, &QPushButton::clicked, this,
            &MainWindow::showLeaderboard);
    connect(ui->searchPushButton, &QPushButton::clicked, this,
            &MainWindow::showSearch);
}

void MainWindow::initWindow() {
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2,
         (desktop->height() - this->height()) / 2);

    ui->personalInfoTableView->setStyleSheet(
        "QTableCornerButton::section{border: none;background:white;}"
        "QHeaderView{ border: none; background:white; }"
        "border: none;background:white;");
    ui->personalInfoTableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->personalInfoTableView->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->personalInfoTableView->verticalHeader()->hide();
    ui->personalInfoTableView->setEditTriggers(
        QAbstractItemView::NoEditTriggers);
    ui->personalInfoTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->personalInfoTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->personalInfoTableView->setUpdatesEnabled(true);
    ui->personalInfoTableView->horizontalHeader()->setDefaultSectionSize(140);
    ui->personalInfoTableView->verticalHeader()->setDefaultSectionSize(50);

    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("Info"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Value"));
    auto personalTable = ui->personalInfoTableView;
    personalTable->setModel(model);
    personalTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 2; j++)
            model->setItem(i, j, new QStandardItem());
    QFont ft;
    ft.setPointSize(14);
    for (int i = 0; i < 4; i++) {
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        model->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        model->item(i, 0)->setFont(ft);
        model->item(i, 1)->setFont(ft);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete model;
}

void MainWindow::setUser(QVariant data) {
    loginInfo = data.value<LoginInfo>();
    qDebug() << "set user";
    if (loginInfo.type == LoginInfo::WORD_BUILDER) {
        wordBuilder = User::instance().getWordBuilder(loginInfo);
        initWordBuilderWindow();
    } else if (loginInfo.type == LoginInfo::CHALLENGER) {
        challenger = User::instance().getChallenger(loginInfo);
        initChallengerWindow();
    }
}

void MainWindow::refreshWordBuilderWindow() {
    model->item(1, 1)->setText(QString::number(wordBuilder.level));
    model->item(2, 1)->setText(QString::number(wordBuilder.exp));
    model->item(3, 1)->setText(QString::number(wordBuilder.build_word));
}

void MainWindow::refreshChallengerWindow() {
    model->item(1, 1)->setText(QString::number(challenger.level));
    model->item(2, 1)->setText(QString::number(challenger.exp));
    model->item(3, 1)->setText(QString::number(challenger.card_pass));
}

void MainWindow::showSingleGame() {
    this->hide();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
    emit toSingleGame();
}

void MainWindow::showDoubleGame() {
    this->hide();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
    emit toMatching();
}
void MainWindow::showSearch() {
    this->hide();
    emit toSearch();
}

void MainWindow::showBuildWord() {
    this->hide();
    QVariant data;
    data.setValue(wordBuilder);
    emit sendWordBuilder(data);
    emit toBuildWord();
}

void MainWindow::showLeaderboard() {
    this->hide();
    emit toLeader();
}

void MainWindow::setChallenger(QVariant data) {
    this->challenger = data.value<Challenger>();
    refreshChallengerWindow();
    delayMsecSuspend(50);
    qDebug() << "set challenger";
    User::instance().updateUser(this->challenger);
}

void MainWindow::setWordBuilder(QVariant data) {
    this->wordBuilder = data.value<WordBuilder>();
    refreshWordBuilderWindow();
    delayMsecSuspend(50);
    qDebug() << "set word builder";
    User::instance().updateUser(this->wordBuilder);
}

void MainWindow::closeAll() { emit sendCloseAll(); }

void MainWindow::refreshAfterDoubleGame() {
    LoginInfo li;
    li.usr = challenger.usr;
    challenger = User::instance().getChallenger(li);

    refreshChallengerWindow();
    this->show();
}

void MainWindow::delayMsecSuspend(int msec) {
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do {
        _NowTimer = QTime::currentTime();
    } while (_Timer.msecsTo(_NowTimer) <= msec);
}

void MainWindow::initWordBuilderWindow() {
    model->item(0, 0)->setText("Username");
    model->item(0, 1)->setText(QString::fromStdString(wordBuilder.usr));
    // level, exp, build_word
    model->item(1, 0)->setText("level");
    model->item(1, 1)->setText(QString::number(wordBuilder.level));
    model->item(2, 0)->setText("exp");
    model->item(2, 1)->setText(QString::number(wordBuilder.exp));
    model->item(3, 0)->setText("num of build");
    model->item(3, 1)->setText(QString::number(wordBuilder.build_word));
    ui->gamePushButton->hide();
    ui->singleModeRadioButton->hide();
    ui->doubleModeRadioButton->hide();
    ui->buildWordPushButton->setDefault(true);
    ui->buildWordPushButton->setShortcut(Qt::Key_Enter);
}

void MainWindow::initChallengerWindow() {
    model->item(0, 0)->setText("Username");
    model->item(0, 1)->setText(QString::fromStdString(challenger.usr));
    // level, exp, card_pass, card_fail, word_eliminate
    model->item(1, 0)->setText("level");
    model->item(1, 1)->setText(QString::number(challenger.level));
    model->item(2, 0)->setText("exp");
    model->item(2, 1)->setText(QString::number(challenger.exp));
    model->item(3, 0)->setText("max card");
    model->item(3, 1)->setText(QString::number(challenger.card_pass));
    ui->buildWordPushButton->hide();
    ui->gamePushButton->setDefault(true);
    ui->gamePushButton->setShortcut(Qt::Key_Enter);
    ui->doubleModeRadioButton->click();
}
