#include "companies.h"
#include "ui_companies.h"
#include "connection.h"

Companies::Companies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Companies)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de empresas");
 ui->comboBox_search->addItem("Rut","rut");
    ui->comboBox_search->addItem("Nombres","names");
    ui->lineEdit_rut->setEnabled(false);
    ui->pushButton_new->setEnabled(false);
    loadTable("default");
}

Companies::~Companies()
{
    delete ui;
}

void Companies::loadTable(QString query){
    //like code from people, created By Cristhopper Quintana,modify and adapt By Juan Morales
    connection conn;
    QSqlQueryModel * TableModal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
	if(query=="default")
    qry->prepare("select rut as 'RUN', name as 'Razón Social' from company order by name asc");
else
        qry->prepare(query);
    if(!qry->exec())
    {
        QMessageBox::critical(this,tr("ERROR"),error1);
        Logger::insert2Logger(rutSignin," ERROR ",error1);
    }
    else
    {
        QSqlQueryModel * TableModal=new QSqlQueryModel();
    TableModal->setQuery(*qry);
    ui->tableView->setModel(TableModal);
    ui->tableView->setColumnWidth(1,300);
}
    delete qry;
}

void Companies::on_lineEdit_search_textChanged(const QString &arg1)
{
    QString qry;
    ui->lineEdit_search->setText(ui->lineEdit_search->text().toUpper());
    if(arg1.isEmpty())
        qry="default";
    else
    {
        int indexSelected = ui->comboBox_search->currentIndex();
        switch(indexSelected)
        {
        case 0: //rut
            qry = "select rut as Rut,name as Nombres from company where rut like '"+arg1+"%'";
            break;
        case 1: //names
            qry = "select rut as Rut,name as Nombres from company where name like '"+arg1+"%'";
            break;
        }
    }
    loadTable(qry);
}

void Companies::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column()==0){
        ui->pushButton_update->setEnabled(true);
        QString rut = ui->tableView->model()->data(index).toString();
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        if(qry->exec("select rut,name from company where rut='"+rut+"'")){
            while (qry->next()){
                ui->lineEdit_rut->setText(rut);
                ui->lineEdit_name->setText(qry->value(1).toString());
            }
        }
        delete qry;
    }
}


void Companies::on_pushButton_update_clicked()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(!ui->lineEdit_name->text().isEmpty()&&!ui->lineEdit_rut->text().isEmpty()){
        if(qry->exec("select * from company where name='"+ui->lineEdit_name->text()+"'")){
            if(!qry->next()){
                qry->exec("update company  set name='"+ui->lineEdit_name->text()+"'where rut='"+ui->lineEdit_rut->text()+"'");
                QMessageBox::information(this,tr("ENHORABUENA"),tr("Empresa Actualizada Correctamente"));
                qDebug()<<qry->lastQuery();
                Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
            }else
                QMessageBox::warning(this,tr("PRECAUCION"),tr("Ya existe una empresa con el mismo nombre"));
        }
    }else{
        QMessageBox::warning(this,tr("ERROR"),tr("Campo Razon Social o RUN vacio, porfavor Verifique e intente nuevamente"));
        Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
        qDebug()<<qry->lastQuery();
    }
    loadTable("default");
    delete qry;
}

void Companies::on_lineEdit_name_textChanged(const QString &arg1)
{
    ui->lineEdit_name->setText(ui->lineEdit_name->text().toUpper());
}

void Companies::on_pushButton_new_clicked()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(qry->exec("select rut from company where rut='"+ui->lineEdit_rut->text()+"'")){
        if(qry->next()){
            QMessageBox::warning(this,tr("PRECAUCION"),"La empresa con RUN='"+ui->lineEdit_rut->text()+"' ya se encuentra en la Base de Datos,porfavor Verifique");
        }else if(ui->lineEdit_name->text().isEmpty()||ui->lineEdit_rut->text().isEmpty())
            QMessageBox::warning(this,tr("PRECAUCION"),"Campos Incompletos, porfavor Verifique");
        else if(!ui->lineEdit_name->text().isEmpty()&&!ui->lineEdit_rut->text().isEmpty()){
            if(qry->exec("select name from company where name='"+ui->lineEdit_name->text()+"'")){
                if(qry->next()){
                    QMessageBox::warning(this,tr("PRECAUCION"),"Ya existe una empresa con el mismo nombre");
                }else{
                    qry->exec("insert into company(rut,name) VALUES('"+ui->lineEdit_rut->text()+"','"+ui->lineEdit_name->text()+"'"+")");
                    qDebug()<<qry->lastQuery();
                    Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
                    QMessageBox::information(this,tr("Enhorabuena"),"Empresa Ingresada Correctamente.");
                    ui->pushButton_update->setEnabled(true);
                    ui->pushButton_new->setEnabled(false);
                    ui->lineEdit_rut->setText("");
                    ui->lineEdit_name->setText("");
                    ui->lineEdit_rut->setEnabled(false);
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
    ui->lineEdit_rut->setText("");
    ui->lineEdit_name->setText("");
    ui->lineEdit_rut->setEnabled(true);
    ui->pushButton_update->setEnabled(false);
    ui->pushButton_new->setEnabled(true);
    ui->tableView->setEnabled(false);
    ui->pushButton_new->setFocus();
}
