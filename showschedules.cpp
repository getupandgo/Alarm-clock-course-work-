#include "showschedules.h"
#include "ui_showschedules.h"

showschedules::showschedules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showschedules)
{
    ui->setupUi(this);
}

showschedules::~showschedules()
{
    delete ui;
}
