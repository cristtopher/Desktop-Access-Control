#ifndef DAILYREPORT_H
#define DAILYREPORT_H

#include <QDialog>

namespace Ui {
class DailyReport;
}

class DailyReport : public QDialog
{
    Q_OBJECT

public:
    explicit DailyReport(QWidget *parent = 0);
    ~DailyReport();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DailyReport *ui;
    enum record{
        ID, STATE, RUT_PEOPLE, NAMES, PATERNAL_SURNAME, MATERNAL_SURNAME, BIRTHDATE,
        NATIONALITY, CELLPHONE, COMPANY ,PROFILE ,POSITION,FREQUENCY, START_AUTHORIZED_DATE,
        END_AUTHORIZED_DATE, START_AUTHORIZED_HOUR, END_AUTHORIZED_HOUR, TYPE, DATETIME_INPUT,
        DATETIME_OUTPUT, PATENT_INPUT, PATENT_OUTPUT, USUARIO, AUTHORIZED_BY,COMMENT, COUNT
    };
};

#endif // DAILYREPORT_H
