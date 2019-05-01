/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:33
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:33
 */
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include "RegisterDialog.h"
namespace Ui {
class LoginDialogUi;
};

/**
 * @brief 登陆界面类
 *
 */
class LoginDialog: public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Login Dialog object
     *
   * 构造时需要初始化ui并连接信号与槽
   * @param parent 继承上一个窗口
   */
    explicit LoginDialog(QWidget* parent = nullptr);
    /**
     * @brief Destroy the Login Dialog object
     *
     */
    ~LoginDialog();

signals:
    /**
     * @brief 发送包裹了用户信息的QVariant的信号
     *
     * @param user
     */
    void sendUser(QVariant user);
    /**
     * @brief 显示注册界面的信号
     *
     */
    void toReg();
    /**
     * @brief 显示主界面的信号
     *
     */
    void toMain();

public slots:


private slots:
    /**
     * @brief 检查登陆密码是否正确
     * 如果密码正确则将用户信息发送到主窗口, 并将主窗口显示出来
     * 否则显示密码错误信息框
     */
    void checkPassword();
    /**
     * @brief 隐藏当前窗口, 显示注册窗口
     *
     */
    void showReg();
    /**
     * @brief 隐藏当前窗口, 显示主窗口
     *
     */
    void showMainWindow();

private:
    Ui::LoginDialogUi * ui; /// ui
    MaterialMessageBox *msg; /// 消息弹窗
};

#endif // LOGINDIALOG_H
