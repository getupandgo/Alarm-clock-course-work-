#include <QCoreApplication>

#include "tcp_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TCPServer news;

    return a.exec();
}
