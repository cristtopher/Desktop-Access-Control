#include "users.h"
#include "ui_users.h"

#include "connection.h"
#include "dashboard.h"
#include <QMessageBox>

Users::Users(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de usuarios");

    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    QPixmap db_ok(":images/Database-Accept-icon.png");
    ui->label_status->setPixmap(db_ok);

    QSqlQueryModel * companyModal=new QSqlQueryModel();
    qry->exec("select name from company");
    companyModal->setQuery(*qry);
    ui->comboBox_company->setModel(companyModal);

    QSqlQueryModel * rolModal=new QSqlQueryModel();
    qry->exec("select name from rol");
    rolModal->setQuery(*qry);
    ui->comboBox_id_rol->setModel(rolModal);

    delete qry;
    loadTable();
}

Users::~Users()
{
    delete ui;
}

void Users::on_pushButton_clicked()
{
    if(Users::validateChnId(ui->lineEdit_rut->text()))
    {
        connection conn;
        QString rut_company = conn.getFirstFromDb(rutSignin,"select rut from company where name='"+ui->comboBox_company->itemText(ui->comboBox_company->currentIndex())+"'");
        QString id_rol = conn.getFirstFromDb(rutSignin,"select id from rol where name='"+ui->comboBox_id_rol->itemText(ui->comboBox_id_rol->currentIndex())+"'");

        QString query="insert into users (rut, names, paternal_surname, password, rut_company, id_rol, maternal_surname) values ('"+ui->lineEdit_rut->text()+"',')"+
                ui->lineEdit_names->text()+"','"+ui->lineEdit_paternal_surname->text()+"','"+ui->lineEdit_password->text()+"','"+rut_company+"',"+id_rol+",'"+ui->lineEdit_maternal_surname->text()+"')";
        if(conn.insert2Db(rutSignin,query)){
            QMessageBox::information(this,tr("INFO"),tr("Usuario agregado exitosamente."));
            Logger::insert2Logger(rutSignin," INFO ", "Usuario agregado exitosamente");
            clean();
            loadTable();
        }
        else
        {
            QMessageBox::critical(this, tr("ERROR"), tr("Error al agregar usuario."));
            Logger::insert2Logger(rutSignin," ERROR ", "Error al agregar usuario.");
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Rut ingresado no es valido."));
        ui->lineEdit_rut->setFocus();
    }
}

void Users::loadTable(){
    connection conn;
    QSqlQueryModel * TableModal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->exec("select u.rut as Rut,u.names as Nombres,u.paternal_surname as 'Apellido Paterno',u.maternal_surname as 'Apellido Materno',c.name as Empresa,r.name as Rol from users as u left join company as c on u.rut_company=c.rut inner join rol as r on u.id_rol=r.id");
    TableModal->setQuery(*qry);
    ui->tableView->setModel(TableModal);
    delete qry;
}

void Users::on_lineEdit_rut_editingFinished()
{
    if(validateChnId(ui->lineEdit_rut->text())==false){
        QMessageBox::critical(this,tr("Error"),tr("Rut invalido"));
        ui->lineEdit_rut->setFocus();
    }
}

void Users::on_lineEdit_names_editingFinished()
{
    ui->lineEdit_names->setText(ui->lineEdit_names->text().toUpper());
}

void Users::on_lineEdit_paternal_surname_editingFinished()
{
    ui->lineEdit_paternal_surname->setText(ui->lineEdit_paternal_surname->text().toUpper());
}

void Users::on_lineEdit_maternal_surname_editingFinished()
{
    ui->lineEdit_maternal_surname->setText(ui->lineEdit_maternal_surname->text().toUpper());
}


bool Users::validateChnId(QString rut)
{
    //vectorizar rut
    /*QVector<QString> vrut(rut.length());
    for (int i = rut.length(); i >= 0 ; i--) {
        vrut.append(rut.at(i));
        qDebug()<<rut.at(i);
    }
    for (int i = 0; i < vrut.size(); ++i) {
        qDebug()<<vrut.at(i);
    }*/
    return true;
}
void Users::on_lineEdit_names_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->styleSheet().contains("QLineEdit { background: rgb(255, 121, 121);}"))
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
}

void Users::on_lineEdit_rut_textChanged()
{
    QString rut = ui->lineEdit_rut->text();
    rut.replace("-", "");
    rut.replace(".","");
    rut.toUpper();
    rut.remove(QRegularExpression("[A-J]"));
    rut.remove(QRegularExpression("[L-Z]"));
    ui->lineEdit_rut->setText(rut);
    if(ui->lineEdit_rut->styleSheet().contains("QLineEdit { background: rgb(255, 121, 121);}"))
        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
}

void Users::on_lineEdit_paternal_surname_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->text().isEmpty())
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
}

void Users::on_lineEdit_maternal_surname_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->text().isEmpty())
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_paternal_surname->text().isEmpty())
//        ui->lineEdit_paternal_surname->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
}

void Users::clean(){
    ui->lineEdit_rut->setText("");
    ui->lineEdit_names->setText("");
    ui->lineEdit_paternal_surname->setText("");
    ui->lineEdit_maternal_surname->setText("");
    ui->lineEdit_password->setText("");
}
