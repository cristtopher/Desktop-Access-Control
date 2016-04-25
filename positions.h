#ifndef POSITIONS_H
#define POSITIONS_H

#include <QDialog>

namespace Ui {
class Positions;
}

class Positions : public QDialog
{
    Q_OBJECT

public:
    explicit Positions(QWidget *parent = 0);
    ~Positions();

private:
    Ui::Positions *ui;
};

#endif // POSITIONS_H
