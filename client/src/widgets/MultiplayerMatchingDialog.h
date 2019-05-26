#ifndef MULTIPLAYERMATCHDIALOG_H
#define MULTIPLAYERMATCHDIALOG_H

#include "tcpclient.h"
#include "ui/MultiPlayerMatchDialog_ui.h"
#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTimer>
#include <QVariant>
#include <materialmessagebox.h>
namespace Ui {
class MultiPlayerMatchDialog;
}

class MultiPlayerMatchDialog : public QDialog {
    Q_OBJECT

public:
    explicit MultiPlayerMatchDialog(QWidget *parent = nullptr);

    /**
     * @brief match player
     *
     */
    void matchPlayer();

    /**
     * @brief Set the Challenger object
     *
     * @param data
     */
    void setChallenger(QVariant data);

    /**
     * @brief Set the Multi Player Tbale object
     *
     * @param table
     */
    void setMultiPlayerTbale(QVector<QVector<QString>> table);
    /**
     * @brief ??????????????
     *
     * @param index ?????
     */
    void competeQuery(QModelIndex index);

    /**
     * @brief ???????, ????????
     *
     * @param table
     */
    void receiveCompeteQuery(const QVector<QVector<QString>> table);

    /**
     * @brief ????, ??????
     *
     */
    void refuseCompete();
    /**
     * @brief ????, ?????????
     *
     */
    void agreeCompete();
signals:
    void toMain();
    /**
     * @brief ????
     *
     * @param data
     */
    void endMatching(QVariant data);
    /**
     * @brief ????
     *
     * @param data
     */
    void beginMatching(QVariant data);

private:
    Ui::MultiPlayerMatchDialog *ui;
    MaterialMessageBox *msg; /// ??????
    QStandardItemModel tableModel;
    Challenger challenger; /// ????
    QVector<QVector<QString>> tempQuery;
    QMessageBox msb; /// ???
};

#endif // MULTIPLAYERMATCHDIALOG_H
