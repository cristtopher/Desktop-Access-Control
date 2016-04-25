#ifndef PEOPLE_H
#define PEOPLE_H

#include <QDialog>

namespace Ui {
class People;
}

class People : public QDialog
{
    Q_OBJECT

public:
    explicit People(QWidget *parent = 0);
    ~People();

private slots:

    void loadTable(QString query);

    void on_lineEdit_rut_editingFinished();

    void on_lineEdit_names_editingFinished();

    void on_lineEdit_paternal_surname_editingFinished();

    void on_lineEdit_maternal_surname_editingFinished();

    void on_lineEdit_email_editingFinished();

    void on_dateEdit_end_editingFinished();

    bool validateChnId(QString rut);

    void on_lineEdit_names_textChanged();

    void on_lineEdit_rut_textChanged();

    void on_lineEdit_paternal_surname_textChanged();

    void on_lineEdit_maternal_surname_textChanged();

    void on_dateEdit_birthdate_userDateChanged();

    void on_comboBox_frequency_currentIndexChanged(int index);

    void on_lineEdit_cellphone_textChanged();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_new_clicked();

    void on_lineEdit_filtered_textChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_update_clicked();

    void on_pushButton_add_clicked();


private:
    Ui::People *ui;
};

#endif // PEOPLE_H
