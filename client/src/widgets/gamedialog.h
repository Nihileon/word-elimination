#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QObject>
#include <QMetaObject>
#include <QVariant>
#include <QTimer>

namespace Ui {
class GameDialogUi;
}

class GameDialog : public QDialog
{

    Q_OBJECT

public:
    explicit GameDialog(QWidget* parent = nullptr);
    void showMain();
    void init();

    void countBegin();
signals:
    void toMain();
    void nextWord();


public slots:




    void countDown();
private:
    Ui::GameDialogUi *ui;
    QTimer* qtimer;
    int counter;
};

#endif // GAMEDIALOG_H
