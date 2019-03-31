#ifndef LEADERBOARDDIALOG_H
#define LEADERBOARDDIALOG_H
#include "data/login.h"
#include "data/word.h"
#include <QDialog>
#include <QVariant>
#include <QMessageBox>
namespace Ui {
class  LeaderboardDialogUi;
}

class LeaderboardDialog: public QDialog
{
    Q_OBJECT
public:
    LeaderboardDialog(QWidget *parent = nullptr);
    void showMain();

signals:
    void toMain();
private:
    Ui::LeaderboardDialogUi* ui;
};

#endif // LEADERBOARDDIALOG_H
