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
#include <QMap>

#include "clientconnection.h"
#include "watcher.h"
#include "../resources/packet.h"

#define PORT_NUMBER 1080

class TCPServer : public QObject
{
    Q_OBJECT

public:
    TCPServer();
    ~TCPServer();

signals:
    void addMember(QTcpSocket *socket);

    void newSchedule(qint32 addr, Schedule news);
    void selectDate(qint32 addr, QString date);
    void removeSchedule(qint32 addr, Schedule remove);
    void postpone(qint32 addr);
    void statistic(qint32 addr);

private:
    QTcpServer *server = NULL;
    QTcpSocket *receiveFromClient = NULL;
    //QTcpSocket *sendToClient = NULL;
    QNetworkSession *networkSession = NULL;

    Watcher *database = NULL;
    qint16 blockSize;
    QDataStream *in = NULL;

private slots:
    void newMember();
    void sessionOpened();

    void onData();
    void decodeNew();
    void decodeSelect();
    void decodeRemove();

    void sendSchedule(qint32 ip, Schedule snd);
    void sendAlarm();
    void sendStatistic(qint32 ip, Schedule snd);
    void sendPostpone(qint32 ip, qint32 postpones);
};

#endif // TCP_SERVER_H
