#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <connection.h>


extern connection conn;
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_open_clicked();

    void on_lineEdit_password_textChanged();

    void on_pushButton_cancel_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
