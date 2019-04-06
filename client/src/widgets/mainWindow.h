#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data/user.h"
#include <QStandardItemModel>
#include <QVariant>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUser(QVariant data );

    void refreshWordBuilderWindow();
    void refreshChallengerWindow();
    void initWordBuilderWindow();
    void initChallengerWindow();
    void initWindow();
    void showBuildWord();
    void Delay_MSec_Suspend(int msec)
    {

        QTime _Timer = QTime::currentTime();

        QTime _NowTimer;
        do{
            _NowTimer=QTime::currentTime();
        }while (_Timer.msecsTo(_NowTimer)<=msec);

    }
    void showLeaderboard();
signals:
    void toGame();
    void toBuildWord();
    void toLeader();
    void toSearch();
    void sendChallenger(QVariant data);
    void sendWordBuilder(QVariant data);
    void sendCloseAll();

public slots:
    void showGame();
    void showSearch();
    void setChallenger(QVariant data);
    void setWordBuilder(QVariant data);
    void closeAll();

private:
    WordBuilder wordBuilder;
    Challenger challenger;
    LoginInfo loginInfo;
    Ui::MainWindow *ui;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
