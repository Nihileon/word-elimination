#include "ui/LeaderboardDialog_ui.h"
#include "LeaderBoardDialog.h"

LeaderboardDialog::LeaderboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeaderboardDialogUi)/*,reg(new RegisterDialog)*/
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);
    connect(ui->backPushButton, &QPushButton::clicked, this,&LeaderboardDialog::showMain);
}

void LeaderboardDialog::showMain()
{
    this->hide();
    emit toMain();
}
