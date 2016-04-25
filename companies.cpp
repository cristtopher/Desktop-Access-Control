#include "companies.h"
#include "ui_companies.h"
#include "connection.h"

Companies::Companies(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Companies)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de empresas");
    loadTable();
}

Companies::~Companies()
{
    delete ui;
}

void Companies::loadTable(){
    connection conn;
    QSqlQueryModel * TableModal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("select rut as 'RUN', name as 'Razón Social' from company order by name asc");
    qry->exec();
    TableModal->setQuery(*qry);
    ui->tableView->setModel(TableModal);
    ui->tableView->setColumnWidth(1,100);
    delete qry;
}
