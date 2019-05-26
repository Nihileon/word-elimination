#ifndef DOUBLEPLAYERDIALOG_H
#define DOUBLEPLAYERDIALOG_H

#include "data/user.h"
#include "data/word.h"
#include "ui/DoublePlayerDialog_ui.h"
#include <QDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTimer>
#include <QVariant>
#include <materialmessagebox.h>
namespace Ui {
class DoublePlayerDialog;
}

class DoublePlayerDialog : public QDialog {
    Q_OBJECT

public:
    explicit DoublePlayerDialog(QWidget *parent = nullptr)
        : QDialog(parent), ui(new Ui::DoublePlayerDialog),
          msg(new MaterialMessageBox(this)), qtimer(new QTimer(this)) {
        ui->setupUi(this);
        setWindowTitle(tr(""));
        setFixedSize(this->width(), this->height());
        QPalette palette(this->palette());
        palette.setColor(QPalette::Background, Qt::white);
        this->setPalette(palette);

        ui->cardTextBrowser->setStyleSheet("border:0px");
        ui->wordTextBrowser->setStyleSheet("border:0px");
        ui->wordLineEdit->setLabel("input what you see.");
        ui->countdownProgressBar->setStyleSheet(
            "border:1px solid "
            "grey;border-radius:2px;text-align:center;background-color:#"
            "ffffff;");
        ui->countdownLcdNumber->hide();
        auto wordBrows = ui->wordTextBrowser;
        wordBrows->setFontPointSize(25);
        wordBrows->setAlignment(Qt::AlignCenter);

        connect(qtimer, &QTimer::timeout, this, &DoublePlayerDialog::countDown);
        connect(ui->nextPushButton, &QPushButton::clicked, this,
                &DoublePlayerDialog::checkCorrect);
        connect(ui->backPushBotton, &QPushButton::clicked, this, &DoublePlayerDialog::quitGame);
    }

/**
 * @brief 游戏开始
 *
 * @param table 单词信息
 */
    void beginGame(QVector<QVector<QString>> table) {
        emit hideMultiPlayerMatchWindow();
        this->show();
        ui->nextPushButton->show();
        ui->nextPushButton->setDefault(true);
        ui->nextPushButton->setShortcut(Qt::Key_Enter);
        ui->wordLineEdit->setFocus();
        ui->wordTextBrowser->show();
        ui->wordLineEdit->clear();
        ui->wordLineEdit->setDisabled(true);
        word = table.at(0).at(0);

        string tr = "<center><big><font size=14>" + word.toStdString() +
            "</big></font></center>";
        QObject::tr(tr.c_str());
        ui->wordTextBrowser->setText(QObject::tr(tr.c_str()));
        auto cntBar = ui->countdownProgressBar;

        cntBar->setValue(5);
        cntBar->setRange(0, 5);
        qDebug() <<word<< cntBar->value();
        qtimer->start(1000);
    }

/**
 * @brief 倒计时, 数到0的时候将单词隐藏
 *
 */
    void countDown() {
        auto cntBar = ui->countdownProgressBar;
        if (cntBar->value() > 0) {
            cntBar->setValue(cntBar->value() - 1);
        } else if (cntBar->value() <= 0) {
            ui->wordTextBrowser->hide();
            ui->wordLineEdit->setDisabled(false);
            ui->wordLineEdit->setFocus();
        } else {
        }
    }

/**
 * @brief 退出游戏, 返回主窗口
 *
 */
    void quitGame() { string data = "WORD_QUIT";
        TCPClient::instance().sendMessage(data);
        emit toMain();
        this->hide();
        qtimer->stop();
    }
    /**
     * @brief 检查单词是否正确, 不正确不做任何操作, 正确则增加经验并返回主窗口
     *
     */
    void checkCorrect() {
        if (word == ui->wordLineEdit->text()) {
            string data = "WORD_CORRECT";
            TCPClient::instance().sendMessage(data);
            qDebug() << "check correct";
            TCPClient::instance().gameEnd();
            qtimer->stop();
        }
    }
signals:
/**
 * @brief 隐藏多人游戏匹配窗口
 *
 */
    void hideMultiPlayerMatchWindow();
    /**
     * @brief 发送拼写正确信号, 让客户端告诉服务器该用户首先拼出了单词
     *
     */
    void spellCorrect();
    /**
     * @brief 返回主窗口
     *
     */
    void toMain();
private:
    Ui::DoublePlayerDialog *ui; /// ui信息
    MaterialMessageBox *msg; /// 信息弹框
    QTimer *qtimer;        /// 定时器
    Challenger challenger; /// 玩家信息
    int counter;           /// 计数器, 用于计算剩余的时间
    QString word; /// 单词信息
};

#endif // DOUBLEPLAYERDIALOG_H
