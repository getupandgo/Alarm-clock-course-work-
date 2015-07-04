#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QNetworkSession>

//#include "constants.h"
#include "clientconnection.h"

#define PORT_NUMBER 1080

class TCPServer : public QObject
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();
signals:
    void addMember(QTcpSocket * socket);
    void deleteMember(QHostAddress);
private:
    QTcpServer *server = NULL;
    QTcpSocket *client = NULL;
    QNetworkSession *networkSession = NULL;

    qint16 blockSize;
    QDataStream *in;
private slots:
    void newMember();
    void sessionOpened();
    void onData();
    void decodeNew();
};

#endif // TCP_SERVER_H
