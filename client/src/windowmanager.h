#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QApplication>
#include "widgets/LoginDialog.h"
#include "widgets/mainWindow.h"
#include "widgets/registerdialog.h"
#include <QObject>

class Manager{
private:
    MainWindow* gw;
    LoginDialog* l;
    RegisterDialog* r;
    static Manager *_instance;

    Manager():gw(new MainWindow),l(new LoginDialog), r(new RegisterDialog){}
public:
    ~Manager(){
        delete gw;
        delete l;
        delete r;
    }
    static Manager& instance();
    static void destroy();
    void init();

};

#endif // WINDOWMANAGER_H
