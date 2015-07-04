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

    client = server->nextPendingConnection();

    if(client){
        qDebug() << '\n' << client->peerAddress().toString() << "connected";

        connect(client, SIGNAL(readyRead()),
                this, SLOT(onData()));

        blockSize = 0;
    }
}

void TCPServer::onData()
{
    in = new QDataStream(client);
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
        emit postpone();
    break;

    default: throw pckt;
    }
    delete in;
}

void TCPServer::decodeNew()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (client->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (client->bytesAvailable() < blockSize)
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

    schedule news(stime, sdate, srepeat);

    emit newSchedule(news);

    blockSize = 0;

}

void TCPServer::decodeSelect()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (client->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (client->bytesAvailable() < blockSize)
        return;

    QByteArray date;
    *in >> date;
    QString sdate(date);

    qDebug() << sdate;

    emit selectDate(sdate);

    blockSize = 0;

}

void TCPServer::decodeRemove()
{
    in->setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (client->bytesAvailable() < (int)sizeof(quint16))
            return;

        *in >> blockSize;
    }

    if (client->bytesAvailable() < blockSize)
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

    schedule removes(stime, sdate, srepeat);

    emit removeSchedule(removes);

    blockSize = 0;

}

TCPServer::~TCPServer()
{
    delete client;
    delete server;
}
