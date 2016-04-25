#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QDialog>

namespace Ui {
class UserProfile;
}

class UserProfile : public QDialog
{
    Q_OBJECT

public:
    explicit UserProfile(QWidget *parent = 0);
    ~UserProfile();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_names_editingFinished();

    void on_lineEdit_paternal_surname_editingFinished();

    void on_lineEdit_maternal_surname_editingFinished();

private:
    Ui::UserProfile *ui;
};

#endif // USERPROFILE_H
