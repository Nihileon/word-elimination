#ifndef BUILDWORDDIALOG_H
#define BUILDWORDDIALOG_H
#include "data/login.h"
#include "data/word.h"
#include <QDialog>
#include <QVariant>
#include <QMessageBox>
namespace Ui {
class  BuildWordDialogUi;
}

class BuildWordDialog: public QDialog
{
    Q_OBJECT
public:
    explicit BuildWordDialog(QWidget* parent = nullptr);
    void showMain();
    void addWord();

signals:
    void toMain();
    void sendWordBuilder(QVariant data);

public slots:
    void setWordBuilder(QVariant data);

private:
    WordBuilder wordBuilder;
    Ui::BuildWordDialogUi *ui;

};

#endif // BUILDWORDDIALOG_H
