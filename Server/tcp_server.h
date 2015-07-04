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
    //void deleteMember(QHostAddress);

    void newSchedule(schedule news);
    void selectDate(QString date);
    void removeSchedule(schedule remove);
    void postpone();

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
    void decodeSelect();
    void decodeRemove();
};

#endif // TCP_SERVER_H
