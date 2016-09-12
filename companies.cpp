#include "companies.h"
#include "ui_companies.h"
#include "connection.h"
QString selectedCompany;
Companies::Companies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Companies)
{

    QStringList header;
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de empresas");
    ui->pushButton_new->setEnabled(false);
    header <<"Razon Social";
    ui->tableView->setColumnCount(header.size());
    ui->tableView->setHorizontalHeaderLabels(header);
    ui->tableView->setColumnWidth(0,500);
    loadTable("default");
}

Companies::~Companies()
{
    delete ui;
}

void Companies::loadTable(QString query){
    //like code from people, created By Cristhopper Quintana,modify and adapt By Juan Morales
    clean("O",false);
    clean("C",false);
    clean("R",false);
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(query=="default")
        qry->prepare("select name from company order by name asc");
    else
        qry->prepare(query);
    if(!qry->exec())
    {
        QMessageBox::critical(this,tr("ERROR"),error1);
        Logger::insert2Logger(rutSignin," ERROR ",error1);
    }
    else
    {
        int row=0;
        while(qry->next()){
            row = ui->tableView->rowCount();
            ui->tableView->insertRow(row);
            ui->tableView->setItem(row,0, new QTableWidgetItem(qry->value(0).toString()));
            // qDebug()<<qry->value(0).toString();
        }
    }
    delete qry;
}

void Companies::on_lineEdit_search_textChanged(const QString &arg1)
{
    QString qry;
    //ui->lineEdit_search->setText(ui->lineEdit_search->text().toUpper());
    if(arg1.isEmpty())
        qry="default";
    else
    {
        arg1.toUpper();
        qry = "select name from company where name like '"+arg1+"%'";
        qDebug ()<<arg1;
    }
    loadTable(qry);
}



void Companies::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column()==0){
        ui->pushButton_update->setEnabled(true);
        QString company = ui->tableView->model()->data(index).toString();
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        if(qry->exec("select name from company where name='"+company+"'")){
            while (qry->next()){
                selectedCompany=qry->value(0).toString();
                ui->lineEdit_name->setText(qry->value(0).toString());
            }
        }
        delete qry;
    }
}


void Companies::on_pushButton_update_clicked()
{
    qDebug()<<ui->lineEdit_name->text();
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(!ui->lineEdit_name->text().isEmpty()){
        if(qry->exec("select name from company where name='"+ui->lineEdit_name->text()+"'")){
            if(!qry->next()){
                qry->exec("update company  set name='"+ui->lineEdit_name->text()+"'where name='"+selectedCompany+"'");
                qDebug ()<<"update company  set name='"+ui->lineEdit_name->text()+"'where name='"+selectedCompany+"'";
                QMessageBox::information(this,tr("ENHORABUENA"),tr("Empresa Actualizada Correctamente"));
                selectedCompany="";
                ui->lineEdit_name->setText("");
                Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
            }else
                if(ui->lineEdit_name->text()==selectedCompany){
                    QMessageBox::warning(this,tr("PRECAUCION"),tr("Empresa ya existe en la base de datos"));
                    selectedCompany="";
                }
        }else{
            QMessageBox::warning(this,tr("ERROR"),tr("Campo Razon Social vacio, porfavor Verifique e intente nuevamente"));
            Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
            //qDebug()<<qry->lastQuery();
        }
        loadTable("default");
        delete qry;
    }
}
void Companies::on_lineEdit_name_textChanged(const QString &arg1)
{
    ui->lineEdit_name->setText(ui->lineEdit_name->text().toUpper());
}

void Companies::on_pushButton_new_clicked()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(qry->exec("select rut from company where name='"+ui->lineEdit_name->text()+"'")){
        if(qry->next()){
            QMessageBox::warning(this,tr("PRECAUCION"),"La empresa '"+ui->lineEdit_name->text()+"' ya se encuentra en la Base de Datos,porfavor Verifique");
        }else if(ui->lineEdit_name->text().isEmpty())
            QMessageBox::warning(this,tr("PRECAUCION"),"Campos Incompletos, porfavor Verifique");
        else if(!ui->lineEdit_name->text().isEmpty()){
            if(qry->exec("select name from company where name='"+ui->lineEdit_name->text()+"'")){
                if(qry->next()){
                    QMessageBox::warning(this,tr("PRECAUCION"),"Ya existe una empresa con el mismo nombre");
                }else{
                    qry->exec("insert into company(name) VALUES('"+ui->lineEdit_name->text()+"'"+")");
                    //ui->qDebug()<<qry->lastQuery();
                    Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
                    QMessageBox::information(this,tr("Enhorabuena"),"Empresa Ingresada Correctamente.");
                    ui->pushButton_update->setEnabled(true);
                    ui->pushButton_new->setEnabled(false);
                    ui->lineEdit_name->setText("");
                    ui->tableView->setEnabled(true);
                    loadTable("default");
                }
            }
        }
        else{
            QMessageBox::critical(this,tr("Error"),"Error al ingresar empresa, contacte con el Administrador del Sistema");
            Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
        }
        loadTable("default");
        delete qry;
    }
}
void Companies::on_pushButton_newCompany_clicked()
{
    ui->lineEdit_name->setText("");
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_new->setEnabled(true);
    ui->tableView->setEnabled(false);
    ui->pushButton_new->setFocus();
}
void Companies::clean(QString type, bool personalPanel)
{
    int i;
    if(type=="O")
    {
        for(i = ui->tableView->rowCount();i>=0;i--)
            ui->tableView->removeRow(i);
    }
    else if(type=="C")
    {
        for(i = ui->tableView->rowCount();i>=0;i--)
            ui->tableView->removeRow(i);
    }
    else if(type=="R")
    {
        for(i = ui->tableView->rowCount();i>=0;i--)
            ui->tableView->removeRow(i);
    }

}
