#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    w = new MainWindow();

    serverSocket = new ServerConnection();

    connect(w, SIGNAL(newConnection(QString,int)),
            this, SLOT(connectToServer(QString,int)));

    //requests to the server
    connect(w, SIGNAL(newSchedule(Schedule)),
            this, SLOT(sendNewSchedule(Schedule)));

    connect(w, SIGNAL(dateRequested(QString)),
            this, SLOT(sendDate(QString)));

    connect(w, SIGNAL(scheduleRemoved(Schedule)),
            this, SLOT(sendRemoved(Schedule)));

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

void Controller::sendRemoved(Schedule removed)
{
    serverSocket->sendRemoved(removed);
}

Controller::~Controller()
{
    delete w;
}
