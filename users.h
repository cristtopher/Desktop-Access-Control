#ifndef USERS_H
#define USERS_H

#include <QDialog>

namespace Ui {
class Users;
}

class Users : public QDialog
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = 0);
    ~Users();

private slots:
    void on_pushButton_clicked();

    void loadTable();

    void on_lineEdit_rut_editingFinished();

    void on_lineEdit_names_editingFinished();

    void on_lineEdit_paternal_surname_editingFinished();

    void on_lineEdit_maternal_surname_editingFinished();

    bool validateChnId(QString rut);

    void on_lineEdit_names_textChanged();

    void on_lineEdit_rut_textChanged();

    void on_lineEdit_paternal_surname_textChanged();

    void on_lineEdit_maternal_surname_textChanged();

    void clean();

private:
    Ui::Users *ui;
};

#endif // USERS_H
