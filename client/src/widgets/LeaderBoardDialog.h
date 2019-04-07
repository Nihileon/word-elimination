#ifndef LEADERBOARDDIALOG_H
#define LEADERBOARDDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QMessageBox>
#include <materialmessagebox.h>
#include "data/user.h"
#include "data/word.h"


namespace Ui {
class  LeaderboardDialogUi;
}

class LeaderboardDialog: public QDialog
{
    Q_OBJECT

public:
    LeaderboardDialog(QWidget *parent = nullptr);
    ~LeaderboardDialog();

signals:
    void toMain();

public slots:
    void showThis();

private slots:
    void showMain();

private:
    Ui::LeaderboardDialogUi* ui;
    QSqlQueryModel* model;
    MaterialMessageBox *msg;

    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;

    void refreshLeaderboard();
    void refreshChallenger();
    void refreshWordBuilder();
};

#endif // LEADERBOARDDIALOG_H
