#include "widgets/mainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/registerdialog.h"
#include "widgets/LoginDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
