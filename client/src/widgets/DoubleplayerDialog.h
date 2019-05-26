#ifndef DOUBLEPLAYERDIALOG_H
#define DOUBLEPLAYERDIALOG_H

#include "data/user.h"
#include "data/word.h"
#include "ui/DoublePlayerDialog_ui.h"
#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTimer>
#include <QVariant>
#include <materialmessagebox.h>
namespace Ui {
class DoublePlayerDialog;
}


/**
 * @brief The DoublePlayerDialog class
 */
class DoublePlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit DoublePlayerDialog(QWidget *parent = nullptr);

    /**
     * @brief 游戏开始
     *
     * @param table 单词信息
     */
    void beginGame(QVector<QVector<QString>> table);

    /**
     * @brief 倒计时, 数到0的时候将单词隐藏
     *
     */
    void countDown();

    /**
     * @brief 退出游戏, 返回主窗口
     *
     */
    void quitGame();
    /**
     * @brief 检查单词是否正确, 不正确不做任何操作, 正确则增加经验并返回主窗口
     *
     */
    void checkCorrect();
signals:
    /**
     * @brief 隐藏多人游戏匹配窗口
     *
     */
    void hideMultiPlayerMatchWindow();
    /**
     * @brief 发送拼写正确信号, 让客户端告诉服务器该用户首先拼出了单词
     *
     */
    void spellCorrect();
    /**
     * @brief 返回主窗口
     *
     */
    void toMain();

private:
    Ui::DoublePlayerDialog *ui; /// ui信息
    MaterialMessageBox *msg;    /// 信息弹框
    QTimer *qtimer;             /// 定时器
    Challenger challenger;      /// 玩家信息
    int counter;                /// 计数器, 用于计算剩余的时间
    QString word;               /// 单词信息
};

#endif // DOUBLEPLAYERDIALOG_H
