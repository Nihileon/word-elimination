/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:27
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:27
 */
#ifndef LEADERBOARDDIALOG_H
#define LEADERBOARDDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QMessageBox>
#include <materialmessagebox.h>
#include <qstandarditemmodel.h>
#include "data/user.h"
#include "data/word.h"


namespace Ui {
class  LeaderboardDialogUi;
}

/**
 * @brief 排行榜类
 *
 */
class LeaderboardDialog: public QDialog
{
    Q_OBJECT

public:
    /**
   * @brief Construct a new Leaderboard Dialog object
   *
   * 构造时需要初始化ui并连接信号与槽
   * @param parent 继承上一个窗口
   */
    explicit LeaderboardDialog(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Leaderboard Dialog object
     *
     */
    ~LeaderboardDialog();

signals:
    /**
     * @brief 显示MainWindow的信号
     *
     */
    void toMain();

public slots:
    /**
     * @brief 显示本窗口的槽
     * 首前先更新窗口, 再显示本窗口
     */
    void showThis();

private slots:
    /**
     * @brief 隐藏本窗口并显示主窗口
     *
     */
    void showMain();

private:
    Ui::LeaderboardDialogUi* ui; /// ui
    QVector<QVector<QString>> model;
    QStandardItemModel tableModel;
    MaterialMessageBox *msg; /// 消息弹窗

    /**
     * @brief 用户类型
     *
     */
    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;

    /**
     * @brief 初始化排行榜
     *
     */
    void refreshLeaderboard();
    /**
     * @brief 更新玩家排行榜
     *
     */
    void refreshChallenger();
    /**
     * @brief 更新出题人排行榜
     *
     */
    void refreshWordBuilder();
};

#endif // LEADERBOARDDIALOG_H
