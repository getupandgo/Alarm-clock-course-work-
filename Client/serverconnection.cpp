#include "serverconnection.h"

ServerConnection::ServerConnection()
{
    sendToServer = new QTcpSocket(this);
    //receiveFromClient = new QTcpSocket(this);

    connect(sendToServer, SIGNAL(readyRead()),
            this, SLOT(onData()));

    connect(sendToServer, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(parseError(QAbstractSocket::SocketError)));
}

void ServerConnection::connectToServer(QString host, int port)
{
    qDebug() << "connecting to the server...";

    try
    {
        sendToServer->connectToHost(host, port);
    }
    catch(QAbstractSocket::SocketError)
    {
        throw;
    }

    if(!sendToServer->waitForConnected(3000))
        qDebug() << "got timeout!"
                 << sendToServer->error();

    blockSize = 0;

}

void ServerConnection::onData()
{
    in = new QDataStream(sendToServer);
    //QByteArray dat =  sendToServer->readAll();
    //qDebug() << dat;
    qint16 packt;
    *in >> packt;


    //blockSize = 0;

    switch(packt)
    {

    case NEW:
        //decodeNew();
    break;

    case SELECT:
        decodeSelect();
    break;

    case REMOVE:
        //decodeRemove();
    break;

    case POSTPONE:
        //decodePostpone();
    break;

    case ALARM:
        emit signalAlarm();
    break;

    default:
        throw packt;

    }

    if(in){
        delete in;
        in = NULL;
    }
}

void ServerConnection::decodeSelect()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (sendToServer->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (sendToServer->bytesAvailable() < blockSize)
        return;

    QByteArray time;
    *in >> time;
    QString stime(time);

    QByteArray date;
    *in >> date;
    QString sdate(date);

    QByteArray repeat;
    *in >> repeat;
    QString srepeat(repeat);

    qDebug() << stime;
    qDebug() << sdate;
    qDebug() << srepeat;

    Schedule news(stime, sdate, srepeat);

    emit receivedSchedule(news);

    blockSize = 0;

    if(!sendToServer->atEnd()){
        onData();
    }

}

void ServerConnection::sendNewSchedule(Schedule created)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)NEW
        << (quint16)0
        << created.time.toUtf8()
        << created.date.toUtf8()
        << created.repeat.toUtf8();

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));

    sendToServer->write(block);

}

void ServerConnection::sendSelectedDate(QString date)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)SELECT
        << (quint16)0
        << date.toUtf8();

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));

    sendToServer->write(block);

}

void ServerConnection::sendRemoved(Schedule removed){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)REMOVE
        << (quint16)0
        << removed.time.toUtf8()
        << removed.date.toUtf8()
        << removed.repeat.toUtf8();

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));

    sendToServer->write(block);
}

void ServerConnection::sendPostpone()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)POSTPONE;

    sendToServer->write(block);

}

void ServerConnection::sendStatistic()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)STATISTIC;

    sendToServer->write(block);

}

void ServerConnection::parseError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        emit connectionError("The host was not found. Please check the "
                             "host name and port settings.");
        break;

    case QAbstractSocket::ConnectionRefusedError:
        emit connectionError("The connection was refused by the peer. "
                             "Make sure the fortune server is running, "
                             "and check that the host name and port "
                             "settings are correct.");
        break;

    default:
        emit connectionError("The following error occurred: " + sendToServer->errorString());

    }

}
