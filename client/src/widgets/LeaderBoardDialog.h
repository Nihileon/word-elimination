#ifndef LEADERBOARDDIALOG_H
#define LEADERBOARDDIALOG_H
#include "data/user.h"
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
    void refreshLeaderboard();
    void refreshChallenger(){
        userType=  CHALLENGER;
        refreshLeaderboard();
    }
    void refreshWordBuilder(){
        userType = WORD_BUILDER;
        refreshLeaderboard();
    }
    void showThis(){
        refreshLeaderboard();
        this->show();
    }
signals:
    void toMain();
private:
    Ui::LeaderboardDialogUi* ui;

    QSqlQueryModel* model;
    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;
};

#endif // LEADERBOARDDIALOG_H
