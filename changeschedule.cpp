#include "changeschedule.h"
#include "ui_changeschedule.h"

changeschedule::changeschedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeschedule)
{
    ui->setupUi(this);
}

changeschedule::~changeschedule()
{
    delete ui;
}
