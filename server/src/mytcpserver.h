#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "data/user.h"
#include "data/word.h"
#include "data/transformation.h"
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    static MyTcpServer *_instance;
    static MyTcpServer &instance();
    static void destroy();
    void init();
    void disconnect();
    void parseAndReply(QString &);
    void run();

signals:

public slots:
    void newConnection();
    QString readMessage();
    void sendMessage(QString& data);
private:
    explicit MyTcpServer(QObject *parent = 0);
    QTcpServer *server;
    QTcpSocket *socket;
};

#endif // MYTCPSERVER_H
