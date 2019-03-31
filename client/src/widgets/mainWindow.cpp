#include "widgets/mainWindow.h"
#include "ui/MainWindow_ui.h"
#include "widgets/registerdialog.h"
#include "widgets/LoginDialog.h"
#include <QObject>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    initWindow();
    connect(ui->gamePushButton, &QPushButton::clicked, this, &MainWindow::showGame);
    connect(ui->buildWordPushButton, &QPushButton::clicked, this, &MainWindow::showBuildWord);
    connect(ui->logoutPushBotton, &QPushButton::clicked, this, &MainWindow::closeAll);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setUser(QVariant data){
    loginInfo = data.value<LoginInfo>();
    if(loginInfo.type == LoginInfo::WORD_BUILDER){
        wordBuilder = Login::instance().getWordBuilder(loginInfo);
        initWordBuilderWindow();
    }else if(loginInfo.type == LoginInfo::CHALLENGER){
        challenger = Login::instance().getChallenger(loginInfo);
        initChallengerWindow();
    }
}

void MainWindow::refreshWordBuilderWindow()
{

}

void MainWindow::refreshChallengerWindow()
{

}

void MainWindow::showGame(){
    this->hide();
    QVariant data;
    data.setValue(challenger);
    emit sendChallenger(data);
    emit toGame();
}

void MainWindow::showBuildWord(){
    this->hide();
    QVariant data;
    data.setValue(wordBuilder);
    emit sendWordBuilder(data);
    emit toBuildWord();
}

void MainWindow::setChallenger(QVariant data)
{
    this->challenger = data.value<Challenger>();
    refreshChallengerWindow();
    try {
        Delay_MSec_Suspend(50);
        Login::instance().updateUser(this->challenger);


    } catch (sqlite::sqlite_exception &e) {
        std::cout << "set Challenger:" << e.what()<<std::endl;
    }

}

void MainWindow::setWordBuilder(QVariant data)
{
    this->wordBuilder = data.value<WordBuilder>();
    refreshWordBuilderWindow();
    try {
        Delay_MSec_Suspend(50);
        Login::instance().updateUser(this->wordBuilder);
    } catch (sqlite::sqlite_exception &e) {
        std::cout << "set WordBuilder:" << e.what()<<std::endl;
    }

}

void MainWindow::closeAll()
{
    emit sendCloseAll();
}

void MainWindow::initWindow(){
    QStandardItemModel* model = new QStandardItemModel();
    //    QStringList labels = QObject::trUtf8("频率,功率,误差").simplified().split(",");
    QStringList labels = QObject::trUtf8("personal info,value").split(",");
    model->setHorizontalHeaderLabels(labels);
    auto personalTable = ui->personalInfoTableView;
    personalTable->setModel(model);
}

void MainWindow::initWordBuilderWindow()
{
    ui->gamePushButton->hide();
    ui->buildWordPushButton->setDefault(true);
    ui->buildWordPushButton->setShortcut(Qt::Key_Enter);
}

void MainWindow::initChallengerWindow()
{
    ui->buildWordPushButton->hide();
    ui->gamePushButton->setDefault(true);
    ui->gamePushButton->setShortcut(Qt::Key_Enter);
}

