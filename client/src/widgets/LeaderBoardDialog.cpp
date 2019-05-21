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
    ui->leaderboardTableView->setModel(&table);
//    QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
//    proxy->setSourceModel(model);
//    ui->leaderboardTableView->setModel(proxy);

    connect(ui->backPushButton, &QPushButton::clicked, this,&LeaderboardDialog::showMain);
    connect(ui->challengerRadioButton, &QtMaterialRaisedButton::toggled, this, &LeaderboardDialog::refreshChallenger);
    connect(ui->wordRadioButton, &QtMaterialRaisedButton::toggled, this, &LeaderboardDialog::refreshWordBuilder);

}

LeaderboardDialog::~LeaderboardDialog(){
    delete  ui;
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
     model.clear();
     table.clear();
     qDebug() << "refresh leaderboard";
    if(userType == CHALLENGER){
        User::instance().getChallengerMakeTable(model);
        table.setColumnCount(5);
        table.setHeaderData(0, Qt::Horizontal, "Username");
        table.setHeaderData(1, Qt::Horizontal, "Level");
        table.setHeaderData(2, Qt::Horizontal, "Exp");
        table.setHeaderData(3, Qt::Horizontal, "Max Passed");
        table.setHeaderData(4, Qt::Horizontal, "Eliminated");
    }else if(userType == WORD_BUILDER){
        User::instance().getWordBuilderMakeTable(model);
        table.setColumnCount(4);
        table.setHeaderData(0, Qt::Horizontal, "Username");
        table.setHeaderData(1, Qt::Horizontal, "Level");
        table.setHeaderData(2, Qt::Horizontal, "Exp");
        table.setHeaderData(3, Qt::Horizontal, "Word Built");
    }

    for (int i = 0; i < model.size(); i++) {
        for (int j = 0; j < model.at(i).size(); j++) {
            if (j == 0) {
                table.setItem(i, j, new QStandardItem(model.at(i).at(j)));
            } else {
                QStandardItem *item = new QStandardItem;
                item->setData(QVariant(model.at(i).at(j).toInt()),
                              Qt::EditRole);
                table.setItem(i, j, item);
            }
        }
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

