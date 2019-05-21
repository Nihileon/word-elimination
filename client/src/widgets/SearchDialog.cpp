/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:51
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:51
 */
#include "SearchDialog.h"
#include "ui/SearchDialog_ui.h"
#include "ui/materialmessagebox.h"
#include <QDesktopWidget>
#include <QLabel>
#include <QObject>
#include <QStandardItemModel>
#include <qtmaterialdialog.h>

SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SearchDialogUi),
      msg(new MaterialMessageBox(this)) {
    initDialog();
    connect(ui->backPushButton, &QPushButton::clicked, this,
            &SearchDialog::showMainWindow);
    connect(ui->searchPushButton, &QPushButton::clicked, this,
            &SearchDialog::search);
    connect(ui->challengerRadioButton, &QtMaterialRadioButton::toggled, this,
            &SearchDialog::refreshFilterComboBox);
    connect(ui->wordRadioButton, &QtMaterialRadioButton::toggled, this,
            &SearchDialog::refreshFilterComboBox);
}

void SearchDialog::initDialog() {
    ui->setupUi(this);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2,
         (desktop->height() - this->height()) / 2);

    ui->searchLineEdit->setLabel("username");
    ui->challengerRadioButton->setChecked(true);
    ui->userTableView->setStyleSheet(
        "border: none;background:white;"
        "QTableCornerButton::section{border: none;background:white;}"
        "QHeaderView{ border: none; background:white; }");
    ui->userTableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->userTableView->verticalHeader()->setStyleSheet(
        "QHeaderView::section {"
        " border: none;background-color:#ffffff;}");
    ui->userTableView->verticalHeader()->hide();
    ui->userTableView->horizontalHeader()->setDefaultSectionSize(140);
    ui->userTableView->verticalHeader()->setDefaultSectionSize(40);
    ui->userTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->userTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->userTableView->setSortingEnabled(true);
    ui->userTableView->setUpdatesEnabled(true);
    ui->userTableView->setShowGrid(false);
    ui->userTableView->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    //    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    //    proxy->setSourceModel(model);
    //    ui->userTableView->setModel(proxy);
    ui->userTableView->setModel(&table);

    ui->wordFilterComboBox->setStyleSheet(
        "QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
        "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top "
        "right;width: 20px;"
        "border-left-width: 1px;border-left-color: white;border-left-style:f;"
        "border-top-right-radius: 3px;"
        "border-bottom-right-radius: 3px;}");
    ui->wordFilterComboBox->addItem("Username");
    ui->wordFilterComboBox->addItem("Level");
    ui->wordFilterComboBox->addItem("Exp");
    ui->wordFilterComboBox->addItem("Word Build");

    ui->challengerFilterComboBox->setStyleSheet(
        "QComboBox {border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;min-width: 9em;}"
        "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top "
        "right;width: 20px;"
        "border-left-width: 1px;border-left-color: white;border-left-style:f;"
        "border-top-right-radius: 3px;"
        "border-bottom-right-radius: 3px;}");
    ui->challengerFilterComboBox->addItem("Username");
    ui->challengerFilterComboBox->addItem("Level");
    ui->challengerFilterComboBox->addItem("Exp");
    ui->challengerFilterComboBox->addItem("Max Passed");
    ui->challengerFilterComboBox->addItem("Eliminated");

    ui->challengerFilterComboBox->show();
    ui->wordFilterComboBox->hide();
}

void SearchDialog::refreshFilterComboBox() {
    if (ui->wordRadioButton->isChecked()) {
        ui->wordFilterComboBox->show();
        ui->challengerFilterComboBox->hide();
    } else if (ui->challengerRadioButton->isChecked()) {
        ui->challengerFilterComboBox->show();
        ui->wordFilterComboBox->hide();
    }
}

SearchDialog::~SearchDialog() {
    delete ui;
}
void SearchDialog::showMainWindow() {
    this->hide();
    emit toMainWindow();
}

void SearchDialog::searchWordBuilder() {
    switch (ui->wordFilterComboBox->currentIndex()) {
    case 0:
        searchType = "user_login";
        break;
    case 1:
        searchType = "level";
        break;
    case 2:
        searchType = "exp";
        break;
    case 3:
        searchType = "build_word";
        break;
    }

}

void SearchDialog::searchChallenger() {
    switch (ui->challengerFilterComboBox->currentIndex()) {
    case 0:
        searchType = "user_login";
        break;
    case 1:
        searchType = "level";
        break;
    case 2:
        searchType = "exp";
        break;
    case 3:
        searchType = "card_pass";
        break;
    case 4:
        searchType = "word_eliminate";
    }

}

void SearchDialog::search() {
       model.clear();
       table.clear();
    if (ui->wordRadioButton->isChecked()) {
        searchWordBuilder();
        table.setColumnCount(4);
        table.setHeaderData(0, Qt::Horizontal, "Username");
        table.setHeaderData(1, Qt::Horizontal, "Level");
        table.setHeaderData(2, Qt::Horizontal, "Exp");
        table.setHeaderData(3, Qt::Horizontal, "Word Built");
        qDebug() << "search word builder";
        User::instance().getSearchWordBuilderMakeTable(
            model, searchType, ui->searchLineEdit->text().toStdString());
    } else if (ui->challengerRadioButton->isChecked()) {
        searchChallenger();
        table.setColumnCount(5);
        table.setHeaderData(0, Qt::Horizontal, "Username");
        table.setHeaderData(1, Qt::Horizontal, "Level");
        table.setHeaderData(2, Qt::Horizontal, "Exp");
        table.setHeaderData(3, Qt::Horizontal, "Max Passed");
        //        model->setHeaderData(4, Qt::Horizontal, "Card_fail");
        table.setHeaderData(4, Qt::Horizontal, "Eliminated");
        qDebug() << "search challenger";
        User::instance().getSearchChallengerMakeTable(
            model, searchType, ui->searchLineEdit->text().toStdString());
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

