#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    w = new MainWindow();

    serverSocket = new ServerConnection();

    //connect(serverSocket, SIGNAL(connectionError(QString)),
            //w->chooseServer, SLOT(displayError(QString)));

    connect(w, SIGNAL(newConnection(QString,int)),
            this, SLOT(connectToServer(QString,int)));

    connect(w, SIGNAL(newSchedule(Schedule)),
            this, SLOT(sendNewSchedule(Schedule)));

    connect(w, SIGNAL(dateRequested(QString)),
            this, SLOT(sendDate(QString)));
}

void Controller::connectToServer(QString ip, int port)
{
    serverSocket->connectToServer(ip, port);
}

void Controller::sendNewSchedule(Schedule created)
{
    serverSocket->sendNewSchedule(created);
}

void Controller::sendDate(QString date)
{
    serverSocket->sendSelectedDate(date);
}

Controller::~Controller()
{
    delete w;
}
