/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:51
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:51
 */
#include <QStandardItemModel>
#include <QObject>
#include <QDesktopWidget>
#include <qtmaterialdialog.h>
#include <QLabel>
#include "ui/SearchDialog_ui.h"
#include "ui/materialmessagebox.h"
#include "SearchDialog.h"

SearchDialog::SearchDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::SearchDialogUi),
    model(new QStandardItemModel),
    msg(new MaterialMessageBox(this))
{
    initDialog();
    connect(ui->backPushButton, &QPushButton::clicked, this, &SearchDialog::showMainWindow);
    connect(ui->searchPushButton, &QPushButton::clicked,this, &SearchDialog::search);
}

void SearchDialog::initDialog(){
    ui->setupUi(this);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width()- this->width())/2, (desktop->height() - this->height())/2);

    ui->userLineEdit->setLabel("username");
    ui->challengerRadioButton->setChecked(true);
    ui->userTableView->setStyleSheet("border: none;background:white;"
                                     "QTableCornerButton::section{border: none;background:white;}"
                                     "QHeaderView{ border: none; background:white; }"
                                     );
    ui->userTableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                                                         " border: none;background-color:#ffffff;}");
    ui->userTableView->verticalHeader()->setStyleSheet("QHeaderView::section {"
                                                       " border: none;background-color:#ffffff;}");
    ui->userTableView->verticalHeader()->hide();
    ui->userTableView->horizontalHeader()->setDefaultSectionSize(140);
    ui->userTableView->verticalHeader()->setDefaultSectionSize(40);
    ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->userTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->userTableView->setUpdatesEnabled(true);
    ui->userTableView->setShowGrid(false);
    ui->userTableView->setModel(model);
    userType = CHALLENGER;
    for(int i=0;i<4;i++)
        for(int j=0;j<2;j++)
            model->setItem(i,j, new QStandardItem());
    QFont ft;
    ft.setPointSize(14);
    for(int i=0;i<4;i++){
        model->item(i,0) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,1) ->setTextAlignment(Qt::AlignCenter);
        model->item(i,0)->setFont(ft);
        model->item(i,1)->setFont(ft);
    }
}

SearchDialog::~SearchDialog(){
    delete ui;
    delete model;
}
void SearchDialog::showMainWindow()
{
    this->hide();
    emit toMainWindow();
}

void SearchDialog::searchWordBuilder(){
    LoginInfo li;
    li.usr = ui->userLineEdit->text().toStdString();
    WordBuilder wordBuilder;
    try{
        wordBuilder = User::instance().getWordBuilder(li);
    }catch(QSqlError &e){
        msg->setText("Not Found");
        msg->showDialog();
        return;
    }
    model->item(0,0)->setText("Username");
    model->item(0,1)->setText(QString::fromStdString(wordBuilder.usr));
    //level, exp, build_word
    model->item(1,0)->setText("level");
    model->item(1,1)->setText(QString::number(wordBuilder.level));
    model->item(2,0)->setText("exp");
    model->item(2,1)->setText(QString::number(wordBuilder.exp));
    model->item(3,0)->setText("num of build");
    model->item(3,1)->setText(QString::number(wordBuilder.build_word));
}
void SearchDialog::searchChallenger(){
    LoginInfo li;
    li.usr = ui->userLineEdit->text().toStdString();
    Challenger challenger;
    try {
        challenger  = User::instance().getChallenger(li);
    } catch (QSqlError &e) {
//        MaterialMessageBox *msg = new MaterialMessageBox(this);
        msg->setText("Not Found");
        msg->showDialog();
        return;
    }
    model->item(0,0)->setText("Username");
    model->item(0,1)->setText(QString::fromStdString(challenger.usr));
    //level, exp, card_pass, card_fail, word_eliminate
    model->item(1,0)->setText("level");
    model->item(1,1)->setText(QString::number(challenger.level));
    model->item(2,0)->setText("exp");
    model->item(2,1)->setText(QString::number(challenger.exp));
    model->item(3,0)->setText("max card");
    model->item(3,1)->setText(QString::number(challenger.card_pass));
}

void SearchDialog::search(){
    if(ui->wordRadioButton->isChecked()){
        searchWordBuilder();
    }else if(ui->challengerRadioButton->isChecked()){
        searchChallenger();
    }
}
