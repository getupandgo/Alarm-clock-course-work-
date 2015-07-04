#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QDataStream>
#include <QTcpSocket>

#include "../resources/packet.h"
#include "../resources/schedule.h"


class ClientConnection : public QObject
{
    Q_OBJECT
public:
    ClientConnection(QTcpSocket* socket);
    void sendSchedule();
    void sendRing();
    void sendStatistics();
public slots:
    void onData();
    //void onNewSchedule(); //(QString time, QString date, QString repeat)
    //void onSelectedDate(QString date);
    //void onDeleted(QString date);
    //void onPostpone(QString date);
private:
    void decodeNew(QDataStream& in);
    void decodeSelect(QDataStream& in);
    void decodeRemove(QDataStream& in);
    //void decodePostpone(QDataStream& in);

    void addNewSchedule(Schedule received);

    QTcpSocket* socket;
};


#endif // CLIENTCONNECTION_H

