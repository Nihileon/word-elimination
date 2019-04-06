#include "BuildWordDialog.h"
#include "ui/BuildWordDialog_ui.h"

#include <QLabel>
#include <qtmaterialdialog.h>
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
        //\TODO: move this code to _ui.h
        QtMaterialDialog *msg = new QtMaterialDialog;
        msg->setParent(this);
        QWidget *dialogWidget = new QWidget;
        QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
        dialogWidget->setLayout(dialogWidgetLayout);
        QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
        QLabel* ql = new QLabel;
        QFont ft;
        ft.setPointSize(14);
        ql->setFont(ft);
        ql->setText("Your have successfully add a word.");
        dialogWidgetLayout->addWidget(ql);
        dialogWidgetLayout->setAlignment(ql, Qt::AlignBottom| Qt::AlignCenter);
        dialogWidgetLayout->addWidget(closeButton);
        dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom| Qt::AlignCenter);
        closeButton->setMaximumWidth(150);
        QVBoxLayout *dialogLayout = new QVBoxLayout;
        msg->setWindowLayout(dialogLayout);
        dialogWidget->setMinimumHeight(150);
        dialogWidget->setMinimumWidth(300);
        dialogLayout->addWidget(dialogWidget);
        connect(closeButton, SIGNAL(pressed()), msg, SLOT(hideDialog()));
        msg->showDialog();
        msg->show();
    } catch (QSqlError &e) {
        //\TODO: move this code to _ui.h
        QtMaterialDialog *msg = new QtMaterialDialog;
        msg->setParent(this);
        QWidget *dialogWidget = new QWidget;
        QVBoxLayout *dialogWidgetLayout = new QVBoxLayout;
        dialogWidget->setLayout(dialogWidgetLayout);
        QtMaterialFlatButton *closeButton = new QtMaterialFlatButton("Close");
        QLabel* ql = new QLabel;
        QFont ft;
        ft.setPointSize(14);
        ql->setFont(ft);
        ql->setText("Your word is exist. Please input another one.");
        dialogWidgetLayout->addWidget(ql);
        dialogWidgetLayout->setAlignment(ql, Qt::AlignBottom| Qt::AlignCenter);
        dialogWidgetLayout->addWidget(closeButton);
        dialogWidgetLayout->setAlignment(closeButton, Qt::AlignBottom| Qt::AlignCenter);
        closeButton->setMaximumWidth(150);
        QVBoxLayout *dialogLayout = new QVBoxLayout;
        msg->setWindowLayout(dialogLayout);
        dialogWidget->setMinimumHeight(150);
        dialogWidget->setMinimumWidth(300);
        dialogLayout->addWidget(dialogWidget);
        connect(closeButton, SIGNAL(pressed()), msg, SLOT(hideDialog()));
        msg->showDialog();
        msg->show();
    }
}
