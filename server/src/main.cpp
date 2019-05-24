#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // create MyTcpServer
    // MyTcpServer constructor will create QTcpServer

    auto server = new MyTcpServer;
    if (server->listen(QHostAddress::Any, 8899)) {
        qDebug() << "start listen";
    } else {
        qDebug() << "listen failed";
    }
    return a.exec();
}
