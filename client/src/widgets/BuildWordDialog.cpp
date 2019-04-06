#include <QLabel>
#include <qtmaterialdialog.h>
#include "ui/BuildWordDialog_ui.h"
#include "ui/materialmessagebox.h"
#include "BuildWordDialog.h"

BuildWordDialog::BuildWordDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::BuildWordDialogUi)
{
    ui->setupUi(this);
    setWindowTitle(tr("BuildWord"));
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);

    ui->newWordLineEdit->setLabel("Please input your word.");

    connect(ui->backPushButton, &QPushButton::clicked, this,&BuildWordDialog::showMain);
    connect(ui->confirmPushBotton, &QPushButton::clicked, this, &BuildWordDialog::addWord);
}

BuildWordDialog::~BuildWordDialog(){
    delete ui;
}

void BuildWordDialog::setWordBuilder(QVariant data){
    this->wordBuilder = data.value<WordBuilder>();
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
    try {
        Word::instance().insert(w);
        wordBuilder.build_word++;
        MaterialMessageBox *msg = new MaterialMessageBox(this);
        msg->setText("Your have successfully add a word.");
        msg->show();
    } catch (QSqlError &e) {
        MaterialMessageBox *msg = new MaterialMessageBox(this);
        msg->setText("Your Word is exist! \nPlease input another one.");
        msg->show();
    }
}
