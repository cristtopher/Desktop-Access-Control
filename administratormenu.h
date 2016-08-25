#ifndef ADMINISTRATORMENU_H
#define ADMINISTRATORMENU_H

#include <QDialog>


namespace Ui {
class administratorMenu;
}

class administratorMenu : public QDialog
{
    Q_OBJECT

public:
    explicit administratorMenu(QWidget *parent = 0);
    ~administratorMenu();


public slots:
    void isAdministrator();


private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    QString deleteUnusedCompany();
    void administrate();


    void on_pushButton_clicked();

private:
    Ui::administratorMenu *ui;
};

#endif // ADMINISTRATORMENU_H
