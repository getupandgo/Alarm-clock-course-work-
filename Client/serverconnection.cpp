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
void ServerConnection::sendNewSchedule(schedule created){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)NEW
        << (quint16)0
        << created.time.toUtf8()
        << created.date.toUtf8()
        //<< created.repeat.size()
        << created.repeat.toUtf8();
        //<< "Hello World, this is a very long text!";

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));

    //qDebug() << (quint16)(block.size() - sizeof(quint16));

/*
    out << created.time.toUtf8()
        << created.date.toUtf8()
        << created.repeat.size() << created.repeat.toUtf8();
*/
    qint64 data_send = socket->write(block);
    qDebug() << data_send << "bytes written!";

    QByteArray dbg = block;   // create a copy to not alter the buffer itself
    dbg.replace('\\', "\\\\"); // escape the backslash itself
    dbg.replace('\0', "\\0");  // get rid of 0 characters
    dbg.replace('\n', "\\n");
    //dbg.replace('"', "\\\"");  // more special characters as you like
    qDebug() << dbg;

}

void ServerConnection::sendSelectedDate(QString date){
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    out << date.toUtf8();

    this->sendData(SELECT, pack);
}

void ServerConnection::sendDeleted(schedule created){
    QByteArray pack;
    QDataStream out(&pack, QIODevice::WriteOnly);

    out << created.time.toUtf8()
        << created.date.toUtf8()
        << created.repeat.size() << created.repeat.toUtf8();

    this->sendData(REMOVE, pack);
}

void ServerConnection::sendPostpone(){
    this->sendData(POSTPONE, NULL);
}

void ServerConnection::sendData(pckg_t type, QByteArray data)
{

    QByteArray dat;
    QDataStream out(&dat, QIODevice::WriteOnly);

    //out //<< (quint16)0
        //<< type
        //<< (qint16)data.size()
        //<< (qint16)(dat.size() - sizeof(qint16))
      //  << data;

    //out.device()->seek(0);
    //out ;

    //qDebug() << (quint16)(dat.size() - sizeof(quint16));



    QByteArray dbg = data;   // create a copy to not alter the buffer itself
    dbg.replace('\\', "\\\\"); // escape the backslash itself
    dbg.replace('\0', "\\0");  // get rid of 0 characters
    dbg.replace('\n', "\\n");
    //dbg.replace('"', "\\\"");  // more special characters as you like
    qDebug() << dbg;

    //if(socket->write(dat) < dat.size())
    //{
     //   qDebug() << "No data written";
    //}
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

    //getFortuneButton->setEnabled(true);
}
