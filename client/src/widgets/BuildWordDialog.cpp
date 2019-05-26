/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 18:49:29
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 19:00:26
 */
#include <QLabel>
#include <qtmaterialdialog.h>
#include "ui/BuildWordDialog_ui.h"
#include "ui/materialmessagebox.h"
#include "BuildWordDialog.h"

BuildWordDialog::BuildWordDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::BuildWordDialogUi),
      msg(new MaterialMessageBox(this)){
    ui->setupUi(this);
    setWindowTitle(tr("BuildWord"));
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    ui->newWordLineEdit->setLabel("Please input your word.");
    ui->wordBuildTableView->setStyleSheet(
        "border: none;background:white;"
        "QTableCornerButton::section{border: none;background:white;}"
        "QHeaderView{ border: none; background:white; }");
    ui->wordBuildTableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->wordBuildTableView->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->wordBuildTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
    ui->wordBuildTableView->verticalHeader()->hide();
    ui->wordBuildTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->wordBuildTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->wordBuildTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->wordBuildTableView->setSortingEnabled(true);
    ui->wordBuildTableView->setShowGrid(false);
    ui->wordBuildTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);


    connect(ui->backPushButton, &QPushButton::clicked, this,&BuildWordDialog::showMain);
    connect(ui->confirmPushBotton, &QPushButton::clicked, this, &BuildWordDialog::addWord);
}

BuildWordDialog::~BuildWordDialog(){
    delete ui;
}

void BuildWordDialog::setWordBuilder(QVariant data){
    this->wordBuilder = data.value<WordBuilder>();
    makeTable();
}

void BuildWordDialog::showMain(){
    QVariant data;
    data.setValue(wordBuilder);
    emit sendWordBuilder(data);
    this->hide();
    emit toMain();
}

void BuildWordDialog::addWord(){
    WordInfo w;
    w.word = ui->newWordLineEdit->text().toStdString();
    w.len = w.word.length();
    w.builder = wordBuilder.usr;
    qDebug() << "add word";
    if(Word::instance().insert(w)){
        wordBuilder.build_word++;
        wordBuilder.exp += 4;
        this->setLevel(wordBuilder);
        msg->setText("Your have successfully add a word.");
        msg->showDialog();
    } else {
        msg->setText("Your Word is exist! \nPlease input another one.");
        msg->showDialog();
    }
    makeTable();
}

void BuildWordDialog::makeTable() {
    model.clear();
    qDebug() << "make table";
    Word::instance().getWordMakeTable(model, wordBuilder.usr);
    tableModel.clear();
    tableModel.setColumnCount(3);
    tableModel.setHeaderData(0, Qt::Horizontal, "Word");
    tableModel.setHeaderData(1, Qt::Horizontal, "Fail Time");
    tableModel.setHeaderData(2, Qt::Horizontal, "Pass Time");
    for (int i = 0; i < model.size(); i++) {
        for (int j = 0; j < model.at(i).size(); j++) {
            if (j == 0) {
                tableModel.setItem(i, j, new QStandardItem(model.at(i).at(j)));
            } else {
                QStandardItem *item = new QStandardItem;
                item->setData(QVariant(model.at(i).at(j).toInt()),
                              Qt::EditRole);
                tableModel.setItem(i, j, item);
            }
        }
    }
    ui->wordBuildTableView->setModel(&tableModel);
}

void BuildWordDialog::setLevel(WordBuilder &wb){
    wb.level = static_cast<int>(log(static_cast<double>(wb.exp)) / log(1.2));
}
