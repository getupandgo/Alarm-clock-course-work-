#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>

#include "newschedule.h"

#include "../resources/packet.h"
#include "../resources/schedule.h"

#define PORT_NUMBER 1080

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    ServerConnection();
    void connectToServer(QString host, int port);

    void sendNewSchedule(Schedule created);
    void sendSelectedDate(QString date);
    void sendRemoved(Schedule removed);
    void sendPostpone();
    viod sendStatistic();

public slots:
    void onData();

signals:
    void gotSchedule();
    void gotRing();
    void gotStatistics();
    void signalAlarm();
    void connectionError(QString error);
    //void gotData(QByteArray, QString);

    void receivedSchedule(Schedule received);

private:
    QTcpSocket *sendToServer = NULL;

    //bad
    qint16 blockSize;
    QDataStream *in = NULL;

private slots:
    void decodeSelect();
    void parseError(QAbstractSocket::SocketError socketError);
};

#endif // SERVERCONNECTION_H

