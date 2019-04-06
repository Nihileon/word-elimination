#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QStandardItemModel>
#include "data/user.h"

namespace Ui {
class SearchDialogUi;
}

class SearchDialog: public QDialog{
    Q_OBJECT
public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

signals:
    void toMainWindow();

public slots:

private slots:
    //back to login dialog
    void showMainWindow();

    //public:
private:
    Ui::SearchDialogUi* ui;
    QStandardItemModel *model;
    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;

    void initDialog();
    void searchChallenger();
    void searchWordBuilder();
    void search();
};

#endif // SEARCHDIALOG_H
