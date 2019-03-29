#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "data/login.h"
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
    void setUser(QVariant data ){
        loginInfo = data.value<LoginInfo>();
        if(loginInfo.type == LoginInfo::WORD_BUILDER){
            wb = Login::instance().getWordBuilder(loginInfo);
        }else if(loginInfo.type == LoginInfo::CHALLENGER){
            c = Login::instance().getChallenger(loginInfo);
        }
    }

    void init(){

    }

signals:
    void toGame();

public slots:
    void showGame();

private:
    WordBuilder wb;
    Challenger c;
    LoginInfo loginInfo;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
