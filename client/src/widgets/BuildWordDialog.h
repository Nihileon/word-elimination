/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 19:00:29
 * @Last Modified by: Nihil Eon
 * @Last Modified time: 2019-05-01 19:03:10
 */
#ifndef BUILDWORDDIALOG_H
#define BUILDWORDDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QMessageBox>
#include <materialmessagebox.h>
#include "data/user.h"
#include "data/word.h"

namespace Ui {
class  BuildWordDialogUi;
}

/**
 * @brief 出题窗口类
 *
 */
class BuildWordDialog: public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Build Word Dialog object
     * 构造时需要初始化ui并连接信号与槽
     * @param parent 继承上一个窗口
     */
    explicit BuildWordDialog(QWidget* parent = nullptr);
    /**
     * @brief Destroy the Build Word Dialog object
     *
     */
    ~BuildWordDialog();

signals:
    /**
     * @brief 去往MainWindow的信号
     *
     */
    void toMain();
    /**
     * @brief 发送出题人信息的信号
     *
     * @param data 包裹了出题人信息的QVarient
     */
    void sendWordBuilder(QVariant data);

public slots:
    /**
     * @brief 隐藏BuildWordDialog并显示MainWindow
     *
     */
    void showMain();
    /**
     * @brief Set the Word Builder object
     * 接收并设置出题人信息
     * @param data
     */
    void setWordBuilder(QVariant data);

private:
    WordBuilder wordBuilder; /// 出题人
    Ui::BuildWordDialogUi *ui; /// ui
    MaterialMessageBox *msg; /// 信息弹框
    /**
     * @brief Set the Level object
     * 设置出题人等级
     *
     * @param wb
     */
    void setLevel(WordBuilder &wb);
    /**
     * @brief 添加单词的槽函数
     * 接受来自ui的单词信息, 给出是否存在的判断并弹出相应窗口
     *
     */
    void addWord();
};

#endif // BUILDWORDDIALOG_H
