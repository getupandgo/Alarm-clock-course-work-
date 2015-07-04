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
        qDebug() << "session opened!";

    } else {
        sessionOpened();
    }
/*
    server = new QTcpServer(this);
    if(!server->listen(QHostAddress::Any, PORT_NUMBER))
        qDebug() << "Server is not listening";
    connect(server, SIGNAL(newConnection()), this, SLOT(newMember()));
    */

    connect(server, SIGNAL(newConnection()), this, SLOT(newMember()));

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
        qDebug() << "Unable to start the server";
        //QMessageBox::critical(this, tr("Fortune Server"),
                             // tr("Unable to start the server: %1.")
                             // .arg(server->errorString()));
        //close();
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
    //statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            //"Run the Fortune Client example now.")
                         //.arg(ipAddress).arg(tcpServer->serverPort()));
    qDebug() << ipAddress << server->serverPort();
}

void TCPServer::newMember(){

    client = server->nextPendingConnection();

    if(client){
        qDebug()<<"connected";
        //connect(newConnection, SIGNAL(disconnected()), this, SLOT(emitDeleteMember()));
        //ClientConnection *t = new ClientConnection(newConnection);

        connect(client, SIGNAL(readyRead()), this, SLOT(onData()));
        //connect(client, SIGNAL(readyRead()), this, SLOT(decodeNew()));
        blockSize = 0;
    }
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

    schedule(stime, sdate, srepeat);

}

void TCPServer::onData()
{
    in = new QDataStream(client);
    qint16 packt;
    *in >> packt;

    switch(packt)
    {

    case NEW:
        decodeNew();
    break;

    case SELECT:
        //decodeSelect();
    break;

    case REMOVE:
        //decodeRemove();
    break;

    case POSTPONE:
        //decodePostpone();
    break;

    default: throw packt;
    }
    //delete in;
}

TCPServer::~TCPServer()
{
    delete client;
    delete server;
}
