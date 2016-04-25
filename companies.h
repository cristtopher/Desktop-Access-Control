#ifndef COMPANIES_H
#define COMPANIES_H

#include <QDialog>

namespace Ui {
class Companies;
}

class Companies : public QDialog
{
    Q_OBJECT

public:
    explicit Companies(QWidget *parent = 0);
    ~Companies();

public:
    void loadTable();

private:
    Ui::Companies *ui;
};

#endif // COMPANIES_H
