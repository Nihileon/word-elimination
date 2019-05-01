/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:48
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:48
 */
#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QVariant>
#include <materialmessagebox.h>

namespace Ui {
class RegisterDialogUi;
}

class RegisterDialog: public QDialog{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Register Dialog object
     *
   * 构造时需要初始化ui并连接信号与槽
   * @param parent 继承上一个窗口
   */
    explicit RegisterDialog(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Register Dialog object
     *
     */
    ~RegisterDialog();

signals:
    /**
     * @brief 显示登录窗口的信号
     *
     */
    void toLogin();
    /**
     * @brief 显示主窗口的信号
     *
     */
    void toMainWindow();
    /**
     * @brief 发送包裹了用户的QVariant
     *
     * @param user
     */
    void sendUser(QVariant user);

public slots:

private slots:
    /**
     * @brief 进行注册
     * 尝试将用户信息写入数据库, 如果用户存在则弹失败窗口,
     * 注册成功后跳入主窗口
     */
    void reg();
    /**
     * @brief 隐藏当前窗口并显示登陆窗口
     *
     */
    void backLogin();
    /**
     * @brief 隐藏当前窗口并显示主窗口
     *
     */
    void showMainWindow();

    //public:
private:
    Ui::RegisterDialogUi* ui; /// ui
    MaterialMessageBox *msg; /// 信息框
};

#endif // REGISTERDIALOG_H
