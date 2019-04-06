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

    //back to login dialog
    void showMainWindow();
    void searchChallenger();
    void searchWordBuilder();
    void search();
signals:
    void toMainWindow();



public slots:


//public:
private:
    Ui::SearchDialogUi* ui;
    enum USER_TYPE{
        CHALLENGER, WORD_BUILDER
    }userType;
    QStandardItemModel *model;
};

#endif // SEARCHDIALOG_H
