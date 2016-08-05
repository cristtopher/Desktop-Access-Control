#ifndef FORMCS_H
#define FORMCS_H

#include <QDialog>

namespace Ui {
class formcs;
}

class formcs : public QDialog
{
    Q_OBJECT

public:
    explicit formcs(QWidget *parent = 0);
    ~formcs();

private slots:
    void on_CancelButton_formcs_clicked();

    void readFromFirstDevice();

    void enrollPeople(QString device);

    void on_pushButton_2_clicked();

    bool readAnverso(QString rut);

    void on_pushButton_renewImage_clicked();

    void on_lineEdit_Enterprise_textChanged(const QString &arg1);

    void on_lineEdit_position_textChanged(const QString &arg1);

    void on_button_manualRegistration_clicked();

    void on_acceptButton_formcs_clicked();


private:
    Ui::formcs *ui;
    enum people
           {
               RUT1,NAMES1,PATERNAL_SURNAME1,BIRTHDATE1,COMPANY1,STATE1,COD_NATIONALITY1,START_AUTHORIZED_HOUR1,
               END_AUTHORIZED_HOUR1,START_AUTHORIZED_DATE1,END_AUTHORIZED_DATE1,CELLPHONE1,EMAIL1,POSITION1,
               PROFILE1,PICTURE1,MATERNAL_SURNAME1,FREQUENCY1
           };

           QByteArray serialData1;
           QString serialBuffer1;
};

#endif // FORMCS_H
