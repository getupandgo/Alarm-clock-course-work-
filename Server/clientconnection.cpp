#include "clientconnection.h"

ClientConnection::ClientConnection(QTcpSocket *socket) : socket(socket) {
    //
    connect(socket, SIGNAL(readyRead()), this, SLOT(onData()));
}

void ClientConnection::onData()
{
    qDebug() << "data received";

    QDataStream in(socket);
    qint32 packt;
    in >> packt;

    switch(packt)
    {

    case NEW:
        decodeNew(in);
    break;

    case SELECT:
        decodeSelect(in);
    break;

    case REMOVE:
        decodeRemove(in);
    break;

    case POSTPONE:
        //decodePostpone(in);
    break;

    default: throw packt;
    }
}

void ClientConnection::decodeNew(QDataStream& in){
    char* rawTime = new char[9];
    char* rawDate = new char[14];
    int repeatSize;

    in >> rawTime
       >> rawDate
       >> repeatSize;

    char* rawRepeat = new char [repeatSize];

    QString time;
    time.fromUtf8(rawTime);
    QString date;
    date.fromUtf8(rawDate);
    QString repeat;
    repeat.fromUtf8(rawRepeat);

    delete rawTime;
    delete rawDate;
    delete rawRepeat;

    schedule received(time,date,repeat);

    addNewSchedule(received);

}

void ClientConnection::addNewSchedule(schedule received){
    qDebug()<<received.time<<received.date<<received.repeat;
}

void ClientConnection::decodeSelect(QDataStream& in){
    char* rawDate = new char[10];

    in >> rawDate;

    QString date(rawDate);
    delete rawDate;

    //search date
    //send date to client

}

void ClientConnection::decodeRemove(QDataStream& in){
    char* rawTime = new char[5];
    char* rawDate = new char[10];
    int repeatSize;

    in >> rawTime
       >> rawDate
       >> repeatSize;

    char* rawRepeat = new char [repeatSize];

    QString time(rawTime);
    QString date(rawDate);
    QString repeat(rawRepeat);

    delete rawTime;
    delete rawDate;
    delete rawRepeat;

    schedule received(time,date,repeat);

    //removeSchedule(received);
}
