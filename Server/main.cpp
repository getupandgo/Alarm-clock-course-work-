#include <QCoreApplication>
#include <iostream>

#include "tcp_server.h"
#include "clientconnection.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TCPServer news;

    qDebug()<<"server created!";

    //ClientConnection* channel = new ClientConnection(QHostAddress("127.0.0.1"));
    QTcpSocket neww;
    ClientConnection* channel = new ClientConnection(&neww);


    return a.exec();
}
