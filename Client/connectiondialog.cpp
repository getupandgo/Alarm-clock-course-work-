#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    ui->connectButton->setDisabled(true);

    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        ui->hostComboBox->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->hostComboBox->addItem(name + QChar('.') + domain);
    }
    if (name != QString("localhost"))
        ui->hostComboBox->addItem(QString("localhost"));

    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            ui->hostComboBox->addItem(ipAddressesList.at(i).toString());
    }

    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            ui->hostComboBox->addItem(ipAddressesList.at(i).toString());
    }

    ui->portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    connect(ui->portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(enableConnectButton()));
    connect(ui->quitButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(ui->connectButton, SIGNAL(clicked()),
            this, SLOT(onConnectButtonClicked()));

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

        ui->connectButton->setEnabled(false);
        //statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }

}

void ConnectionDialog::enableConnectButton()
{

    ui->connectButton->setEnabled(//(!networkSession || networkSession->isOpen()) &&
                                 !ui->hostComboBox->currentText().isEmpty() &&
                                 !ui->portLineEdit->text().isEmpty());
}

void ConnectionDialog::displayError(QString error){
    QMessageBox::information(this, tr("Alarm Clock"), error);
}

void ConnectionDialog::sessionOpened()
{
    // Save the used configuration
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

    //statusLabel->setText(tr("This examples requires that you run the "
                            //"Fortune Server example as well."));

    //ui->connectButton->setEnabled();

}

void ConnectionDialog::onConnectButtonClicked()
{
    emit newConnection(ui->hostComboBox->currentText(),
                    ui->portLineEdit->text().toInt());

    this->setVisible(false);
    this->deleteLater();
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}
