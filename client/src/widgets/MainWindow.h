/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:42
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:42
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVariant>
#include <materialmessagebox.h>
#include "data/user.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief 主窗口类
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Main Window object
     *
   * 构造时需要初始化ui并连接信号与槽
   * @param parent 继承上一个窗口
   */
    explicit MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Main Window object
     *
     */
    ~MainWindow();

signals:
    /**
     * @brief 显示游戏窗口的信号
     *
     */
    void toSingleGame();
    /**
     * @brief 显示出题界面的信号
     *
     */
    void toMatching();
    void toBuildWord();
    /**
     * @brief 显示排行榜的信号
     *
     */
    void toLeader();
    /**
     * @brief 显示搜索界面的信号
     *
     */
    void toSearch();
    /**
     * @brief 发送包裹了玩家信息的QVariant
     *
     * @param data
     */
    void sendChallenger(QVariant data);
    /**
     * @brief 发送包含出题人信息的QVariant
     *
     * @param data
     */
    void sendWordBuilder(QVariant data);
    /**
     * @brief 关闭所有窗口的信号
     *
     */
    void sendCloseAll();

public slots:
    /**
     * @brief Set the User object
     * 接受并设置用户信息
     * @param data
     */
    void setUser(QVariant data );
    /**
     * @brief Set the Challenger object
     * 更新数据库中的玩家信息
     * @param data
     */
    void setChallenger(QVariant data);
    /**
     * @brief Set the Word Builder object
     * 更新数据库中的出题人信息
     * @param data
     */
    void setWordBuilder(QVariant data);
    /**
     * @brief 终止主进程, 关闭所有窗口
     *
     */
    void closeAll();
    void refreshAfterDoubleGame() {
        LoginInfo li;
        li.usr = challenger.usr;
        challenger = User::instance().getChallenger(li);

        refreshChallengerWindow();
        this->show();
    }
private slots:
    /**
     * @brief 隐藏当前窗口, 显示游戏界面
     *
     */
    void showSingleGame();
    /**
     * @brief 隐藏当前窗口, 显示搜索界面
     */
    void showDoubleGame();
    void showSearch();
    /**
     * @brief 隐藏当前窗口, 显示出题界面
     *
     */
    void showBuildWord();
    /**
     * @brief 隐藏当前窗口, 显示排行榜
     *
     */
    void showLeaderboard();

private:
    WordBuilder wordBuilder; /// 出题者信息
    Challenger challenger; /// 玩家信息
    LoginInfo loginInfo; /// 登陆信息
    Ui::MainWindow *ui; /// ui
    QStandardItemModel* model; /// 表格模型
    MaterialMessageBox *msg; /// 消息窗口

    /**
     * @brief 更新出题人的窗口
     *
     */
    void refreshWordBuilderWindow();
    /**
     * @brief 更新玩家的窗口
     *
     */
    void refreshChallengerWindow();
    /**
     * @brief 初始化出题人窗口
     * 在侧边窗口显示出题人信息
     */
    void initWordBuilderWindow();
    /**
     * @brief 初始化为玩家窗口
     * 在侧边表格显示玩家信息
     */
    void initChallengerWindow();
    /**
     * @brief 窗口的基本初始化
     *
     */
    void initWindow();
    /**
     * @brief 延时
     * 写入数据库可能会失败, 所以添加一个延时
     * @param msec 延时的时长
     */
    void delayMsecSuspend(int msec);
};

#endif // MAINWINDOW_H
