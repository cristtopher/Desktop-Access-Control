#include "administratormenu.h"
#include "ui_administratormenu.h"
#include <qdebug.h>
#include <qserialport.h>
#include <dashboard.h>
#include <QSerialPort>
#include <connection.h>
#include <qmessagebox.h>
bool administrator=false;

administratorMenu::administratorMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administratorMenu)
{

    QPixmap greenIcon(":images/ok.png");
    QPixmap redIcon(":images/bad.png");
    ui->setupUi(this);
    this->setWindowTitle("Control de Accesos - Menu Administracion");
    ui->label_Administrator->setPixmap(redIcon);
    ui->label_labelExecution->setPixmap(redIcon);
    ui->lineEdit->setFocus();
    connect(RTScan, SIGNAL(readyRead()),this,SLOT(isAdministrator()));
}

administratorMenu::~administratorMenu()
{
    delete ui;
}

void administratorMenu::on_lineEdit_textChanged(const QString &arg1)
{
}
void administratorMenu::isAdministrator(){
    QPixmap greenIcon(":images/ok.png");
    QPixmap redIcon(":images/bad.png");
    QString serialBuffer;
    QString serialData = RTScan->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    QStringList bufferSplit = serialBuffer.split(" ");
    QString rut = bufferSplit[0].toUtf8();
    ui->lineEdit->setText(rut);
    ui->lineEdit->setText("");
    if(rut=="olURh15N3PrXankKZtoQAxEzZoReSetRoUtE"){
        administrator=true;
        ui->label_Administrator->setPixmap(greenIcon);
        disconnect(RTScan, SIGNAL(readyRead()),this,SLOT(isAdministrator()));
        connect(RTScan, SIGNAL(readyRead()),this,SLOT(administrate()));
    }
}
void administratorMenu::administrate(){
    QString i;
    QString serialBuffer;
    QString serialData = RTScan->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    QStringList bufferSplit = serialBuffer.split(" ");
    QString rut = bufferSplit[0].toUtf8();
    QPixmap greenIcon(":images/ok.png");
    QPixmap redIcon(":images/bad.png");
    qDebug()<<"rut: "+rut;
    if(rut=="olURh15N3PrXankKZtoQAxEzZoReSetCoMpAnIe"&&administrator==true){
        QMessageBox msgBox;
        msgBox.setText("Ha seleccionado el codigo:\n\nEliminar empresas que no se utilizan de la base de datos.\nDesea Ejecutar la tarea de Mantenimiento?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setIcon(QMessageBox::Warning);
        int ret = msgBox.exec();;
        switch (ret) {
        case QMessageBox::Ok:
            ui->label_labelExecution->setPixmap(greenIcon);
            i=deleteUnusedCompany();
            QMessageBox::information(this,"MANTENIMIENTO","Se han eliminado exitosamente: '"+i+"' Compañias");
            Logger::insert2Logger(rutSignin, " MANTENIMIENTO ","Se eliminaron'"+i+"'Compañias");
            ui->label_labelExecution->setPixmap(redIcon);
            break;
        case QMessageBox::Cancel:
            msgBox.close();
            break;
        }
    }
}

QString administratorMenu::deleteUnusedCompany(){
    connection conn;
    int count=0;
    QString deletedCompany;
    QSqlQuery* queryCompany=new QSqlQuery(conn.mydb);
    QSqlQuery* queryPeople=new QSqlQuery(conn.mydb);
    QSqlQuery* queryDelete=new QSqlQuery(conn.mydb);
    queryCompany->exec("select * from company");
    while(queryCompany->next()){
        QString temp=queryCompany->value(0).toString();//vale A
        if(queryPeople->exec("select * from people where rut_company='"+temp+"'")&&queryPeople->next()==false)//if has next dont remove
        {
            queryDelete->exec("delete from company where rut='"+temp+"'");
            qDebug()<<"la compañia "+temp+"ha sido eliminada";
            ++count;
        }
    }
    deletedCompany=QString::number(count);
    delete queryCompany,queryDelete,queryPeople;
    conn.connClose();
    return deletedCompany;
}


void administratorMenu::on_pushButton_clicked()
{
}
