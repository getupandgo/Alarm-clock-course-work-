#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "serverconnection.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

signals:

public slots:
    void connectToServer(QString ip, int port);

    void sendNewSchedule(schedule created);
    void sendDate(QString date);

private:
    MainWindow* w = NULL;

    ServerConnection *serverSocket;
    ConnectionDialog *chooseServer = NULL;
};

#endif // CONTROLLER_H
