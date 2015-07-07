#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmWidget), postpones(0)
{
    ui->setupUi(this);

    connect(ui->acceptButton, SIGNAL(pressed()),
            this, SLOT(onAcceptButtonPressed()));

    connect(ui->postponeButton, SIGNAL(pressed()),
            this, SLOT(onPostponeButtonPressed()));
}

void AlarmWidget::onPostponeButtonPressed()
{
    this->setVisible(false);

    ++postpones;

    emit postpone();
}

void AlarmWidget::onAcceptButtonPressed()
{
    this->setVisible(false);
    this->deleteLater();
}

AlarmWidget::~AlarmWidget()
{
    delete ui;
}
