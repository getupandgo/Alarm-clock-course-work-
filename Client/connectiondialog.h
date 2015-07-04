#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QNetworkConfigurationManager>
#include <QSettings>
#include <QMessageBox>
#include <QNetworkSession>

#include "serverconnection.h"

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

private:
    Ui::ConnectionDialog *ui;
    QNetworkSession *networkSession; //?

signals:
    void newConnection(QString ip, int port);

private slots:
    void enableConnectButton();
    void displayError(QString error);
    void onConnectButtonClicked();
    void sessionOpened();
};

#endif // CONNECTIONDIALOG_H
