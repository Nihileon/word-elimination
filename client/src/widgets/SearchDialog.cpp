/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:51
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:51
 */
#include <QDesktopWidget>
#include <QLabel>
#include <QObject>
#include <QStandardItemModel>
#include <qtmaterialdialog.h>
#include "SearchDialog.h"
#include "ui/SearchDialog_ui.h"
#include "ui/materialmessagebox.h"


SearchDialog::SearchDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SearchDialogUi), model(new QSqlQueryModel),
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
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width() - this->width()) / 2,
         (desktop->height() - this->height()) / 2);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

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
    QSortFilterProxyModel *proxy = new QSortFilterProxyModel(this);
    proxy->setSourceModel(model);
    ui->userTableView->setModel(proxy);

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
    delete model;
}
void SearchDialog::showMainWindow() {
    this->hide();
    emit toMainWindow();
}

void SearchDialog::searchWordBuilder() {
    std::string searchType;
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
    User::instance().getSearchWordBuilderMakeTable(
        model, searchType, ui->searchLineEdit->text().toStdString());
}

void SearchDialog::searchChallenger() {
    std::string searchType;
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
    User::instance().getSearchChallengerMakeTable(
        model, searchType, ui->searchLineEdit->text().toStdString());
}

void SearchDialog::search() {
    if (ui->wordRadioButton->isChecked()) {
        searchWordBuilder();
    } else if (ui->challengerRadioButton->isChecked()) {
        searchChallenger();
    }
}
