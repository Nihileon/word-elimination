/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:24
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:24
 */
#include <QRadioButton>
#include <qtmaterialradiobutton.h>
#include <qtmaterialraisedbutton.h>
#include "ui/LeaderboardDialog_ui.h"
#include "LeaderBoardDialog.h"

LeaderboardDialog::LeaderboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderboardDialogUi),/*,reg(new RegisterDialog)*/
    model(new QSqlQueryModel),
    msg(new MaterialMessageBox(this))
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    ui->leaderboardTableView->setStyleSheet(
        "border: none;background:white;"
        "QTableCornerButton::section{border: none;background:white;}"
        "QHeaderView{ border: none; background:white; }");
    ui->leaderboardTableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->leaderboardTableView->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->leaderboardTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->leaderboardTableView->verticalHeader()->hide();
    ui->leaderboardTableView->setEditTriggers(
        QAbstractItemView::NoEditTriggers);
    ui->leaderboardTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leaderboardTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->leaderboardTableView->setSortingEnabled(true);
    ui->leaderboardTableView->setShowGrid(false);
    ui->leaderboardTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    userType = CHALLENGER;
    refreshLeaderboard();
    QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    ui->leaderboardTableView->setModel(proxy);

    connect(ui->backPushButton, &QPushButton::clicked, this,&LeaderboardDialog::showMain);
    connect(ui->challengerRadioButton, &QtMaterialRaisedButton::toggled, this, &LeaderboardDialog::refreshChallenger);
    connect(ui->wordRadioButton, &QtMaterialRaisedButton::toggled, this, &LeaderboardDialog::refreshWordBuilder);

}

LeaderboardDialog::~LeaderboardDialog(){
    delete  ui;
    delete model;
}

void LeaderboardDialog::showMain(){
    this->hide();
    emit toMain();
}

void LeaderboardDialog::showThis(){
    refreshLeaderboard();
    this->show();
}

void LeaderboardDialog::refreshLeaderboard(){
    if(userType == CHALLENGER){
        User::instance().getChallengerMakeTable(model);
    }else if(userType == WORD_BUILDER){
        User::instance().getWordBuilderMakeTable(model);
    }

}

void LeaderboardDialog::refreshChallenger(){
    userType = CHALLENGER;
    refreshLeaderboard();
}

void LeaderboardDialog::refreshWordBuilder(){
    userType = WORD_BUILDER;
    refreshLeaderboard();
}

