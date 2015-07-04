#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    w = new MainWindow();

    serverSocket = new ServerConnection();

    connect(serverSocket, SIGNAL(connectionError(QString)),
            w->chooseServer, SLOT(displayError(QString)));

    connect(w, SIGNAL(newSchedule(schedule)),
            this, SLOT(sendNewSchedule(schedule)));

    connect(w, SIGNAL(newConnection(QString,int)),
            this, SLOT(connectToServer(QString,int)));

}

void Controller::connectToServer(QString ip, int port)
{
    serverSocket->connectToServer(ip, port);

}

void Controller::sendNewSchedule(schedule created)
{
    serverSocket->sendNewSchedule(created);
}

Controller::~Controller()
{
}
