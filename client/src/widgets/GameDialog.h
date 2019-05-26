/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:18
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:18
 */
#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include "data/user.h"
#include "data/word.h"
#include <QDialog>
#include <QMessageBox>
#include <QMetaObject>
#include <QObject>
#include <QTimer>
#include <QVariant>
#include <cmath>
#include <materialmessagebox.h>

namespace Ui {
class GameDialogUi;
}

/**
 * @brief 游戏窗口
 *
 */
class GameDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Construct a new Game Dialog object
     *
     * 构造时需要初始化ui并连接信号与槽
     * @param parent 继承上一个窗口
     */
    explicit GameDialog(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Game Dialog object
     *
     */
    ~GameDialog();

signals:
    /**
     * @brief 显示MainWindow的信号
     *
     */
    void toMain();
    /**
     * @brief 获取一个单词的信号
     *
     */
    void toNextWord();
    /**
     * @brief 发送包裹了出题人的QVariant
     *
     * @param data
     */
    void sendChallenger(QVariant data);

public slots:
    /**
     * @brief 开始游戏的槽
     * 设置关卡信息, 初始化ui并显示单词
     */
    void gameBegin();
    /**
     * @brief Set the Challenger object
     * 接受并设置玩家信息
     * @param data 包裹了玩家信息
     */
    void setChallenger(QVariant data);

private slots:
    /**
     * @brief 隐藏当前窗口并显示主窗口
     *
     */
    void showMain();
    /**
     * @brief 倒计时
     * 倒计时, 如果超时则显示隐藏单词并让文本框变为可写
     */
    void countDown();
    /**
     * @brief 检查输入是否有误
     * 检查单词输入的正确性
     * 如果输入正确则增加单词的通过次数, 更新单词信息, 获取单词经验,
     * 更新用户信息 否则游戏结束
     */
    void checkCorrect();
    /**
     * @brief Get the next Word object
     * 由于作为槽无法调用有参数的函数, 所以包裹了nextWord函数, 详情见nextWord
     */
    void getNextWord();

private:
    Ui::GameDialogUi *ui;    /// ui
    QTimer *qtimer;          /// 定时器
    MaterialMessageBox *msg; /// 交互消息框
    Challenger challenger;   /// 玩家信息
    int counter;             /// 计数器, 用于计算剩余的时间
    WordInfo wordInfo;       /// 单词信息
    int wordLen = 5;         /// 单词长度
    /**
     * @brief 关卡信息
     *
     */
    struct CardInfo {
        int cardPassWordNum; /// 通过的关卡数
        int wordDisplayTime; /// 该关卡对应的单词的显示时间
        int exp;             /// 通过该关卡能获得的经验
        int wordLen;         /// word length from wordLen-3 to wordLen
    } cardInfo;
    int card = 1;        /// 现在的关卡数, 默认为1
    int timePerWord = 0; /// 每个单词的显示时间

    /**
     * @brief Get the CardInfo object
     * 获得关卡信息
     * @param card 第几关
     * @return CardInfo 返回关卡信息
     */
    CardInfo getCardPassInfo(int card);
    /**
     * @brief 设置玩家等级
     *
     */
    void setLevel();
    /**
     * @brief Set the Challenger object
     * 更新本地的玩家信息
     * 如果通过关卡数大于原有记录则更新记录
     * 发送玩家信息给数据库
     */
    void setLocalChallenger();
    /**
     * @brief Set the Card Info object
     * 获取该关卡的信息并初始化关卡设置
     */
    void setCardInfo();
    /**
     * @brief 获取下一个单词
     * 更新ui,
     * 获取符合当前长度的单词[len-3,len)
     * 初始化定时器并开始计时
     * @param len 获取的单词长度上限, 默认为5
     *
     */
    void nextWord(int len = 5);
    /**
     * @brief 闯关失败时
     * 停止定时器, 更新单词信息, 显示失败对话框, 最后初始化关卡
     */
    void gameOver();
    /**
     * @brief 更新数据库的延迟
     * 防止写入失败
     * @param msec 延时时长
     */
    void delayMsecSuspend(int msec);
    /**
     * @brief 设置当前关卡数
     *
     * @param card 关卡数
     */
    void setCard(int card);
    /**
     * @brief Get the Word Exp
     * 获取当前单词所能得到的经验值
     * @return int
     */
    int getWordExp();
};

#endif // GAMEDIALOG_H
