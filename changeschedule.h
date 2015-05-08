#ifndef CHANGESCHEDULE_H
#define CHANGESCHEDULE_H

#include <QWidget>

namespace Ui {
class changeschedule;
}

class changeschedule : public QWidget
{
    Q_OBJECT

public:
    explicit changeschedule(QWidget *parent = 0);
    ~changeschedule();

private:
    Ui::changeschedule *ui;
};

#endif // CHANGESCHEDULE_H
