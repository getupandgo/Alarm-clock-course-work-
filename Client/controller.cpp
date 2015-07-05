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

    //answers from the server
    connect(serverSocket, SIGNAL(receivedSchedule(Schedule)),
            w, SIGNAL(displaySchedule(Schedule)));
}

void Controller::connectToServer(QString ip, int port)
{
    serverSocket->connectToServer(ip, port);
}

void Controller::sendNewSchedule(Schedule created)
{
    serverSocket->sendNewSchedule(created);
    //serverSocket->sendPostpone();
}

void Controller::sendDate(QString date)
{
    serverSocket->sendSelectedDate(date);
}

Controller::~Controller()
{
    delete w;
}
