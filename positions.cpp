#include "positions.h"
#include "ui_positions.h"
#include "connection.h"

Positions::Positions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Positions)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de cargos");
    connection conn;
    QSqlQueryModel * TableModal=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    qry->prepare("select name as 'Cargo' from position order by name asc");
    qry->exec();
    TableModal->setQuery(*qry);
    ui->tableView->setModel(TableModal);
    delete qry;
}

Positions::~Positions()
{
    delete ui;
}
