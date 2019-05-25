#ifndef MULTIPLAYERMATCHDIALOG_H
#define MULTIPLAYERMATCHDIALOG_H

#include "ui/MultiPlayerMatchDialog_ui.h"
#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTimer>
#include <QVariant>
#include <materialmessagebox.h>
#include "tcpclient.h"
namespace Ui {
class MultiPlayerMatchDialog;
}

class MultiPlayerMatchDialog : public QDialog {
    Q_OBJECT

public:
    explicit MultiPlayerMatchDialog(QWidget *parent = nullptr)
        : QDialog(parent), ui(new Ui::MultiPlayerMatchDialog),
          msg(new MaterialMessageBox(this)) {
        ui->setupUi(this);
        setWindowTitle(tr(""));
        setFixedSize(this->width(), this->height());
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::white);
        this->setPalette(palette);
        ui->tableView->setStyleSheet(
            "border: none;background:white;"
            "QTableCornerButton::section{border: none;background:white;}"
            "QHeaderView{ border: none; background:white; }");
        ui->tableView->horizontalHeader()->setStyleSheet(
            "QHeaderView::section {"
            " border: none;background-color:#ffffff;}");
        ui->tableView->verticalHeader()->setStyleSheet(
            "QHeaderView::section {"
            " border: none;background-color:#ffffff;}");
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            QHeaderView::ResizeToContents);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
        ui->tableView->setDragDropMode(QAbstractItemView::NoDragDrop);
        ui->tableView->setSortingEnabled(true);
        ui->tableView->setShowGrid(false);
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            QHeaderView::Stretch);
        ui->tableView->setModel(&tableModel);
        msg->anotherButton->show();
        connect( ui->tableView,&QTableView::clicked,this, &MultiPlayerMatchDialog::competeQuery);

        connect(ui->backPushButton, &QPushButton::clicked, [&]() {
            this->hide();
            QVariant qv;
            qv.setValue(challenger);
            emit endMatching(qv);
            emit toMain();
        });
        //        connect(msg->closeButton, &QtMaterialFlatButton::pressed,
        //        this,
        //                &MultiPlayerMatchDialog::refuseCompete);
        //        connect(msg->anotherButton, &QtMaterialFlatButton::pressed,
        //        this,
        //                &MultiPlayerMatchDialog::agreeCompete);
        //        QtMaterialRaisedButton agree("agree");
        //        QtMaterialRaisedButton refuse("refuse");
        //        msb.addButton(&agree,QMessageBox::AcceptRole);
        // msb.addButton(&refuse,QMessageBox::RejectRole);
        msb.addButton("yes", QMessageBox::AcceptRole);
        msb.addButton("refuse", QMessageBox::RejectRole);
        msb.setStyleSheet("border: none;background-color:#ffffff;");
    }
    void matchPlayer() {
        this->show();
        QVariant qv;
        qv.setValue(challenger);
        emit beginMatching(qv);
    }

    void setChallenger(QVariant data) {
        this->challenger = data.value<Challenger>();
    }
    void setMultiPlayerTbale(QVector<QVector<QString>> table) {
        tableModel.clear();
        qDebug() << "refresh multi table";
        tableModel.setColumnCount(2);
        tableModel.setHeaderData(0, Qt::Horizontal, "Username");
        tableModel.setHeaderData(1, Qt::Horizontal, "Level");
        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table.at(i).size(); j++) {
                if (j == 0) {

                    tableModel.setItem(i, j, new QStandardItem(table.at(i).at(j)));
                } else {
                    QStandardItem *item = new QStandardItem;
                    item->setData(QVariant(table.at(i).at(j).toInt()),
                                  Qt::EditRole);
                    tableModel.setItem(i, j, item);
                }
            }
        }
    }

    void competeQuery(QModelIndex index) {
        std::string otherSide = index.data().toString().toStdString();
        if (index.column() == 0 && otherSide != this->challenger.usr) {
            std::string data = "COMPETE_QUERY|";
            data.append(otherSide);
            TCPClient::instance().sendMessage(data);
        }
    }

    void receiveCompeteQuery(const QVector<QVector<QString>> table) {
        tempQuery = table;
        msb.setText("Level " + table.at(0).at(1) + " user\" " +
                    table.at(0).at(0) + "\" wants to compete with you");
        if (msb.exec() == QMessageBox::AcceptRole) {
            agreeCompete();
        } else {
            refuseCompete();

        }

//        msg->setText("Level " + table.at(0).at(1) + " user\" " +
//                     table.at(0).at(0) + "\" wants to compete with you");
//        msg->showDialog();

    }

    void refuseCompete(){
        qDebug() << "clicked close";
        TCPClient::instance().sendRefuseCompeteQuery(
            QString::fromStdString(transformation::tableToString(tempQuery)));
    }
    void agreeCompete(){
        qDebug() << "clicked anotherbutton";
        //            emit
        //            agreeCompeteQuery(QString::fromStdString(transformation::tableToString(table)));
        TCPClient::instance().sendAgreeCompeteQuery(
            QString::fromStdString(transformation::tableToString(tempQuery)));}
signals:
    void toMain();
    void endMatching(QVariant data);
    void beginMatching(QVariant data);
//    void refuseCompeteQuery(QString qs);
//    void agreeCompeteQuery(QString qs);
//    void refuseCompeteQuery();
//     void agreeCompeteQuery();
private:
    Ui::MultiPlayerMatchDialog *ui;
    MaterialMessageBox *msg; /// 信息弹框
//    QVector<QVector<QString>> model;
    QStandardItemModel tableModel;
    Challenger challenger;
    QVector<QVector<QString>> tempQuery;
    QMessageBox msb;
};

#endif // MULTIPLAYERMATCHDIALOG_H
