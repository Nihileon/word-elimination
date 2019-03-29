#include "widgets/mainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/registerdialog.h"
#include "widgets/LoginDialog.h"
#include <QObject>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    connect(ui->gamePushButton, &QPushButton::clicked, this, &MainWindow::showGame);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showGame(){
    this->hide();
    emit toGame();
}
