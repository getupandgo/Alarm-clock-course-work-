#include "tcp_server.h"

TCPServer::TCPServer() : server(0), networkSession(0)
{
    qDebug() << "starting server...";

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()),
                this, SLOT(sessionOpened()));

        networkSession->open();

    } else {
        sessionOpened();
    }

    connect(server, SIGNAL(newConnection()),
            this, SLOT(newMember()));

    database = new Watcher();

    connect(this, SIGNAL(newSchedule(qint32, Schedule)),
            database, SLOT(addNewSchedule(qint32, Schedule)));

    connect(this, SIGNAL(selectDate(qint32, QString)),
            database, SLOT(searchSelected(qint32, QString)));

    connect(this, SIGNAL(postpone(qint32)),
            database, SLOT(onPostpone(qint32)));

    connect(database, SIGNAL(sendSchedule(qint32, Schedule)),
            this, SLOT(sendSchedule(qint32, Schedule)));

}

void TCPServer::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    server = new QTcpServer(this);
    if (!server->listen()) {
        qDebug() << "\nunable to start the server : " << server->errorString();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qDebug() << "\nserver is running on:\nIP:\n" << ipAddress << "\nport:\n"<< server->serverPort();
}

void TCPServer::newMember(){

    receiveFromClient = server->nextPendingConnection();

    if(receiveFromClient){
        qDebug() << '\n' << receiveFromClient->peerAddress().toString() << "connected";

        connect(receiveFromClient, SIGNAL(readyRead()),
                this, SLOT(onData()));

        blockSize = 0;
    }
}

void TCPServer::onData()
{
    in = new QDataStream(receiveFromClient);
    qint16 pckt;
    *in >> pckt;

    switch(pckt)
    {

    case NEW:
        qDebug() << "\ngot NEW";
        decodeNew();
    break;

    case SELECT:
        qDebug() << "\ngot SELECT";
        decodeSelect();
    break;

    case REMOVE:
        qDebug() << "\ngot REMOVE";
        decodeRemove();
    break;

    case POSTPONE:
        qDebug() << "\ngot POSTPONE";
        emit postpone(receiveFromClient->peerAddress().toIPv4Address());
    break;

    default: throw pckt;
    }
    delete in;
}

void TCPServer::decodeNew()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (receiveFromClient->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (receiveFromClient->bytesAvailable() < blockSize)
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

    blockSize = 0;

    emit newSchedule(receiveFromClient->peerAddress().toIPv4Address(), news);

}

void TCPServer::decodeSelect()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (receiveFromClient->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (receiveFromClient->bytesAvailable() < blockSize)
        return;

    QByteArray date;
    *in >> date;
    QString sdate(date);

    qDebug() << sdate;

    emit selectDate(receiveFromClient->peerAddress().toIPv4Address(), sdate);

    blockSize = 0;

}

void TCPServer::decodeRemove()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (receiveFromClient->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (receiveFromClient->bytesAvailable() < blockSize)
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

    Schedule removes(stime, sdate, srepeat);

    emit removeSchedule(receiveFromClient->peerAddress().toIPv4Address(), removes);

    blockSize = 0;

}

void TCPServer::sendSchedule(qint32 ip, Schedule snd)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)SELECT
        << (quint16)0
        << snd.time.toUtf8()
        << snd.date.toUtf8()
        << snd.repeat.toUtf8();

    out.device()->seek(sizeof(quint16));
    out << (quint16)(block.size() - 2 * sizeof(quint16));
    //bad
    receiveFromClient->write(block);
}

TCPServer::~TCPServer()
{
    delete receiveFromClient;
    delete server;
}
