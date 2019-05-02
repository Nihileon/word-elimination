/*
 * @Author: Nihil Eon
 * @Date: 2019-05-01 20:16:56
 * @Last Modified by:   Nihil Eon
 * @Last Modified time: 2019-05-01 20:16:56
 */
#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QStandardItemModel>
#include <materialmessagebox.h>
#include "data/user.h"

namespace Ui {
class SearchDialogUi;
}

class SearchDialog: public QDialog{
    Q_OBJECT
public:
    /**
     * @brief Construct a new Search Dialog object
     *
   * 构造时需要初始化ui并连接信号与槽
   * @param parent 继承上一个窗口
   */
    explicit SearchDialog(QWidget *parent = nullptr);
    /**
     * @brief Destroy the Search Dialog object
     *
     */
    ~SearchDialog();

signals:
    /**
     * @brief 显示主窗口的信号
     *
     */
    void toMainWindow();

public slots:

private slots:
    /**
     * @brief 隐藏当前窗口并显示主窗口
     *
     */
    void showMainWindow();

    //public:
private:
    Ui::SearchDialogUi* ui; /// ui
    //    QStandardItemModel *model; // 表格模型
    QSqlQueryModel *model; ///sqlModel
    MaterialMessageBox *msg; /// 消息窗口
    /**
     * @brief 用户类型
     *
     */
    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;

    /**
     * @brief 初始化窗口和表格
     *
     */
    void initDialog();
    /**
     * @brief refreshFilterComboBox
     */
    void refreshFilterComboBox();
    /**
     * @brief 搜索玩家, 并在表格中显示
     *
     */
    void searchChallenger();
    /**
     * @brief 搜索出题人, 并在表格中显示
     *
     */
    void searchWordBuilder();
    /**
     * @brief 进行搜索的槽
     * 判断搜索类型为出题人还是玩家
     */
    void search();
};

#endif // SEARCHDIALOG_H
