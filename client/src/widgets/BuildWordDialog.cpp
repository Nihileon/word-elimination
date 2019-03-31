#include "BuildWordDialog.h"
#include "ui/BuildWordDialog_ui.h"
BuildWordDialog::BuildWordDialog(QWidget* parent):
    QDialog (parent),
    ui(new Ui::BuildWordDialogUi)
{
    ui->setupUi(this);
    setWindowTitle(tr("BuildWord"));
    setFixedSize(this->width(), this->height());
    connect(ui->backPushButton, &QPushButton::clicked, this,&BuildWordDialog::showMain);
    connect(ui->confirmPushBotton, &QPushButton::clicked, this, &BuildWordDialog::addWord);
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
        QMessageBox msg;
        msg.setText("you successfully build a add word");
        msg.setWindowModality(Qt::NonModal);
        msg.setStandardButtons(QMessageBox::Close);
        msg.exec();
    } catch (sqlite::sqlite_exception &e) {
        QMessageBox msg;
        msg.setText("you word is exist, pleas input a new one");
        msg.setWindowModality(Qt::NonModal);
        msg.setStandardButtons(QMessageBox::Close);
        msg.exec();
    }
}
