#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVariant>
#include "data/user.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void toGame();
    void toBuildWord();
    void toLeader();
    void toSearch();
    void sendChallenger(QVariant data);
    void sendWordBuilder(QVariant data);
    void sendCloseAll();

public slots:
    void setUser(QVariant data );
    void setChallenger(QVariant data);
    void setWordBuilder(QVariant data);
    void closeAll();

private slots:
    void showGame();
    void showSearch();
    void showBuildWord();
    void showLeaderboard();

private:
    WordBuilder wordBuilder;
    Challenger challenger;
    LoginInfo loginInfo;
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    void refreshWordBuilderWindow();
    void refreshChallengerWindow();
    void initWordBuilderWindow();
    void initChallengerWindow();
    void initWindow();
    void delayMsecSuspend(int msec);
};

#endif // MAINWINDOW_H
