#ifndef INDIVIDUALREPORT_H
#define INDIVIDUALREPORT_H

#include <QDialog>

namespace Ui {
class IndividualReport;
}

class IndividualReport : public QDialog
{
    Q_OBJECT

public:
    explicit IndividualReport(QWidget *parent = 0);
    ~IndividualReport();

private slots:
    void on_pushButton_search_clicked();

    void clean();

    void on_toolButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IndividualReport *ui;
    enum record{
        ID, STATE, RUT_PEOPLE, NAMES, PATERNAL_SURNAME, MATERNAL_SURNAME, BIRTHDATE,
        NATIONALITY, CELLPHONE, COMPANY ,PROFILE ,POSITION,FREQUENCY, START_AUTHORIZED_DATE,
        END_AUTHORIZED_DATE, START_AUTHORIZED_HOUR, END_AUTHORIZED_HOUR, TYPE, DATETIME_INPUT,
        DATETIME_OUTPUT, PATENT_INPUT, PATENT_OUTPUT, USUARIO, AUTHORIZED_BY, PENSION_QUOTES,
        SECURITY_ELEMENTS, COMMENT, COUNT
    };
};

#endif // INDIVIDUALREPORT_H
