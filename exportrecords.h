#ifndef EXPORTRECORDS_H
#define EXPORTRECORDS_H

#include <QDialog>
#include <QAxBase>

namespace Ui {
class ExportRecords;
}

class ExportRecords : public QDialog
{
    Q_OBJECT

public:
    explicit ExportRecords(QWidget *parent = 0);
    ~ExportRecords();

private slots:
    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ExportRecords *ui;
    enum record{
        ID, STATE, RUT_PEOPLE, NAMES, PATERNAL_SURNAME, MATERNAL_SURNAME, BIRTHDATE,
        NATIONALITY, CELLPHONE, COMPANY ,PROFILE ,POSITION,FREQUENCY, START_AUTHORIZED_DATE,
        END_AUTHORIZED_DATE, START_AUTHORIZED_HOUR, END_AUTHORIZED_HOUR, TYPE, DATETIME_INPUT,
        DATETIME_OUTPUT, PATENT_INPUT, PATENT_OUTPUT, USUARIO, AUTHORIZED_BY, PENSION_QUOTES,
        SECURITY_ELEMENTS, COMMENT, COUNT
    };
};

#endif // EXPORTRECORDS_H
