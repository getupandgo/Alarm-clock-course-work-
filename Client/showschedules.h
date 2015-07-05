#ifndef SHOWSCHEDULES_H
#define SHOWSCHEDULES_H

#include <QWidget>
#include <QWidgetItem>

#include "../resources/schedule.h"

namespace Ui {
class ShowSchedules;
}

class ShowSchedules : public QWidget
{
    Q_OBJECT

public:
    explicit ShowSchedules(QWidget *parent = 0);
    ~ShowSchedules();

signals:
    void dateRequested(QString date);

private slots:
    void onSelectionChanged();
    void onChangeButtonClicked();
    void onDeleteButtonClicked();

    void onScheduleReceived(Schedule received);

private:
    Ui::ShowSchedules *ui;
};

#endif // SHOWSCHEDULES_H
