#ifndef REJECTEDREPORT_H
#define REJECTEDREPORT_H

#include <QDialog>

namespace Ui {
class RejectedReport;
}

class RejectedReport : public QDialog
{
    Q_OBJECT

public:
    explicit RejectedReport(QWidget *parent = 0);
    ~RejectedReport();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RejectedReport *ui;
    enum record{
        ID, STATE, RUT_PEOPLE, NAMES, PATERNAL_SURNAME, MATERNAL_SURNAME, BIRTHDATE,
        NATIONALITY, CELLPHONE, COMPANY ,PROFILE ,POSITION,FREQUENCY, START_AUTHORIZED_DATE,
        END_AUTHORIZED_DATE, START_AUTHORIZED_HOUR, END_AUTHORIZED_HOUR, TYPE, DATETIME_INPUT,
        DATETIME_OUTPUT, PATENT_INPUT, PATENT_OUTPUT, USUARIO, AUTHORIZED_BY, COMMENT, COUNT
    };
};

#endif // REJECTEDREPORT_H
