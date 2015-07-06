#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmWidget)
{
    ui->setupUi(this);

    connect(ui->acceptButton, SIGNAL(pressed()),
            this, SLOT(onAcceptButtonPressed()));

    connect(ui->postponeButton, SIGNAL(pressed()),
            this, SIGNAL(postpone()));
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
