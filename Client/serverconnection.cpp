#include "serverconnection.h"

ServerConnection::ServerConnection()
{
    socket = new QTcpSocket(this);
    //connect(socket, SIGNAL(readyRead()),
            //this, SLOT(onData()));

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(parseError(QAbstractSocket::SocketError)));
}

void ServerConnection::connectToServer(QString host, int port)
{
    qDebug() << "connecting to the server...";

    try
    {
        socket->connectToHost(host, port);
    }
    catch(QAbstractSocket::SocketError)
    {
        throw;
    }

    if(!socket->waitForConnected(3000))
        qDebug() << "got timeout!"
                 << socket->error();

}

/*
void ServerConnection::onData()
{
    QDataStream in(socket);
    qint32 packt;
    in >> packt;

    switch(packt)
    {

    case NEW:
        decodeNew();
    break;

    case SELECT:
        decodeSelect();
    break;

    case REMOVE:
        decodeRemove();
    break;

    case POSTPONE:
        decodePostpone();
    break;

    default: throw packt;
    }
}
*/
void ServerConnection::sendNewSchedule(schedule created)
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

    socket->write(block);

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

    socket->write(block);

}

void ServerConnection::sendDeleted(schedule created){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)REMOVE
        << (quint16)0
        << created.time.toUtf8()
        << created.date.toUtf8()
        << created.repeat.toUtf8();

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));

    socket->write(block);
}

void ServerConnection::sendPostpone()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)POSTPONE;

    socket->write(block);

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
        emit connectionError("The following error occurred: " + socket->errorString());

    }

}
