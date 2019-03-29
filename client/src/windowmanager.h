#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include <QApplication>
#include "widgets/LoginDialog.h"
#include "widgets/mainWindow.h"
#include "widgets/registerdialog.h"
#include "widgets/gamedialog.h"
#include <QObject>

class Manager{
private:
    MainWindow* mw;
    LoginDialog* l;
    RegisterDialog* r;
    GameDialog* g;
    static Manager *_instance;

    Manager():mw(new MainWindow),l(new LoginDialog), r(new RegisterDialog),g(new GameDialog){}
public:
    ~Manager(){
        delete mw;
        delete l;
        delete r;
        delete g;
    }
    static Manager& instance();
    static void destroy();
    void init();

};

#endif // WINDOWMANAGER_H
