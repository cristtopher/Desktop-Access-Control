#include "userprofile.h"
#include "ui_userprofile.h"
#include "connection.h"

UserProfile::UserProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Perfile de usuario");
    QPixmap userPix(":images/user.png");
    ui->label_user->setPixmap(userPix);

    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("select * from user where rut='"+rutSignin+"'");
    qry->exec();
    while(qry->next()){
        ui->lineEdit_rut->setText(rutSignin);
        ui->lineEdit_names->setText(qry->value(1).toString());
        ui->lineEdit_paternal_surname->setText(qry->value(2).toString());
        ui->lineEdit_maternal_surname->setText(qry->value(6).toString());
        ui->lineEdit_password->setText(qry->value(3).toString());
    }
}

UserProfile::~UserProfile()
{
    delete ui;
}

void UserProfile::on_pushButton_clicked()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("UPDATE user SET names = '"+ui->lineEdit_names->text()+
                 "', paternal_surname = '"+ui->lineEdit_paternal_surname->text()+"', maternal_surname = '"+ui->lineEdit_maternal_surname->text()+
                 "', password = '"+ui->lineEdit_password->text()+"' where rut='"+rutSignin+"'");
    if(!qry->exec())
    {
        QMessageBox::critical(this,tr("Error al actualizar"),error1);
        Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
    }
    else
    {
        QMessageBox::information(this,"ACTUALIZACION", tr("Usuario actualizado exitosamente."));
        Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
    }
    delete qry;
}

void UserProfile::on_pushButton_2_clicked()
{
    this->close();
}

void UserProfile::on_lineEdit_names_editingFinished()
{
    ui->lineEdit_names->setText(ui->lineEdit_names->text().toUpper());
}

void UserProfile::on_lineEdit_paternal_surname_editingFinished()
{
    ui->lineEdit_paternal_surname->setText(ui->lineEdit_paternal_surname->text().toUpper());
}

void UserProfile::on_lineEdit_maternal_surname_editingFinished()
{
    ui->lineEdit_maternal_surname->setText(ui->lineEdit_maternal_surname->text().toUpper());
}
