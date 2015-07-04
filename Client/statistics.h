#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>

namespace Ui {
class statistics;
}

class statistics : public QWidget
{
    Q_OBJECT

public:
    explicit statistics(QWidget *parent = 0);
    ~statistics();

private:
    Ui::statistics *ui;
};

#endif // STATISTICS_H
