#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QDialog>

namespace Ui {
class AlarmWidget;
}

class AlarmWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmWidget(QWidget *parent = 0);
    ~AlarmWidget();

signals:
    void postpone();

private slots:
    void onPostponeButtonPressed();
    void onAcceptButtonPressed();

private:
    Ui::AlarmWidget *ui;
};

#endif // ALARMWIDGET_H
