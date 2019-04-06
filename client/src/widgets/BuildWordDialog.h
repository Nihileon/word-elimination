#ifndef BUILDWORDDIALOG_H
#define BUILDWORDDIALOG_H

#include <QDialog>
#include <QVariant>
#include <QMessageBox>
#include "data/user.h"
#include "data/word.h"

namespace Ui {
class  BuildWordDialogUi;
}

class BuildWordDialog: public QDialog
{
    Q_OBJECT

public:
    explicit BuildWordDialog(QWidget* parent = nullptr);
    ~BuildWordDialog();

signals:
    void toMain();
    void sendWordBuilder(QVariant data);

public slots:
    void showMain();
    void addWord();
    void setWordBuilder(QVariant data);

private:
    WordBuilder wordBuilder;
    Ui::BuildWordDialogUi *ui;
};

#endif // BUILDWORDDIALOG_H
