#include "readwithoutci.h"
#include "ui_readwithoutci.h"

#include <QMessageBox>
#include "connection.h"
#include <QDateTime>
#include <dashboard.h>
#include <QInputDialog>

bool hasInput;

ReadWithoutCI::ReadWithoutCI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadWithoutCI)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Registro Manual");

    QPixmap db_ok(":images/Database-Accept-icon.png");
    QPixmap db_bad(":images/Database-Delete-icon.png");
    QPixmap user(":images/User-blue-icon.png");
    ui->lineEdit_rut->setFocus();
    ui->label_user->setPixmap(user);
    connection conn;
    if(conn.isOpenDB())
        ui->label_status->setPixmap(db_bad);
    else
        ui->label_status->setPixmap(db_ok);
}

ReadWithoutCI::~ReadWithoutCI()
{
    delete ui;
}

void ReadWithoutCI::on_pushButton_search_clicked()
{
    if(ui->lineEdit_rut->text().isEmpty())
    {
        QMessageBox::critical(this,tr("Error"),tr("Ingrese rut"));
        ui->lineEdit_rut->setFocus();
    }
    else
    {
        QPixmap user(":images/User-blue-icon.png");
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        if(!qry->exec("select p.names, p.paternal_surname, p.maternal_surname, c.name, pro.name, p.picture from people as p LEFT JOIN company as c on p.rut_company=c.rut LEFT JOIN profile as pro on p.id_profile=pro.id where p.rut='" + ui->lineEdit_rut->text()+"'"))
        {
            QMessageBox::critical(this,tr("Error al realizar la busqueda"),error1);
            Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
        }
        else
        {
            bool ishere=false;
            if(qry->next()){

                if(!qry->value(0).toString().isEmpty())
                    ishere=true;
                else
                    ishere=false;
                ui->lineEdit_names->setText(qry->value(0).toString());
                ui->lineEdit_paternal_surname->setText(qry->value(1).toString());
                ui->lineEdit_maternal_surname->setText(qry->value(2).toString());
                ui->lineEdit_company->setText(qry->value(3).toString());
                ui->lineEdit_profile->setText(qry->value(4).toString());
                if(!qry->value(5).toString().isEmpty())
                    user.load(qry->value(5).toString());
                ui->label_user->setPixmap(user);
                ui->lineEdit_patent_input->setText(conn.getFirstFromDb(rutSignin,"select patent_input from record where state='O' and rut_people='"+ui->lineEdit_rut->text()+"'"));

                QSqlQueryModel *modal=new QSqlQueryModel();
                if(!qry->exec("select datetime_input from record where state='O' and rut_people='"+ui->lineEdit_rut->text()+"'"))
                {
                    qApp->beep();
                    QMessageBox::critical(this,tr("Error al registrar"),error1);
                    Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
                }
                else
                {
                    modal->setQuery(*qry);
                    if(modal->rowCount()>0){
                        ui->listView_imput->setModel(modal);
                        ui->listView_imput->setEnabled(true);
                        ui->lineEdit_patent_output->setEnabled(true);
                        ui->lineEdit_comment->setEnabled(true);
                        hasInput = true;
                    }
                    else
                    {
                        ui->lineEdit_patent_input->setEnabled(true);
                        ui->lineEdit_comment->setEnabled(true);
                        if(ui->lineEdit_profile->text().contains("CONTRATISTA")){
                            ui->checkBox_security->setEnabled(true);
                            ui->checkBox_pension->setEnabled(true);
                        }
                        hasInput = false;
                    }
                }
            }

            if(ishere==false)
            {
                qApp->beep();
                QMessageBox::warning(this, tr("Alerta"), tr("Rut no encontrado"));
                clean();
            }
            else{}
        }
        delete qry;
    }
}

QString ReadWithoutCI::verifyPeople()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if (!qry->exec("select state,start_authorized_date,end_authorized_date,start_authorized_hour,end_authorized_hour,id_frequency from people where rut='"+ui->lineEdit_rut->text()+"'"))
    {
        qApp->beep();
        QMessageBox::critical(this,tr("ERROR"),error1);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
    }
    else if (qry->first())
    {
        QString state=qry->value(0).toString();
        QDate startDate = QDate::fromString(qry->value(1).toString(),"yyyy-MM-dd");
        QDate endDate = QDate::fromString(qry->value(2).toString(),"yyyy-MM-dd");
        QTime startTime = QTime::fromString(qry->value(3).toString(),"H:mm");
        QTime endTime = QTime::fromString(qry->value(4).toString(),"H:mm");
        int freq = qry->value(5).toInt();
        bool ok;
        QString recordState;
        QString authorizedBy;
        QTime currentTime = QTime::currentTime();
        QDate currentDate = QDate::currentDate();

        //Autorizher
        QStringList authorizer;
        QSqlQuery* qury=new QSqlQuery(conn.mydb);
        qury->prepare("select names from users where id_rol=2");
        if(!qury->exec())
        {
            QMessageBox::critical(this,tr("ERROR"),error1);
            Logger::insert2Logger(rutSignin," ERROR ",error1);
        }
        else
            while(qury->next())
                authorizer << qury->value(0).toString();
        delete qury;

        if(state == "I") //People Inactive.
        {
            qApp->beep();
            do
                authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Persona no activa.\n\n Solicite autorizacion e indique quien autoriza, en caso contrario presione boton cancelar."),authorizer,0,false,&ok);
            while(ok && authorizedBy.isEmpty());
            if (ok)
            {
                Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" no activa pero autorizada por "+authorizedBy);
                authorizedBy = "[INACTIVO]: " + authorizedBy;
                recordState = "O";
            }
            else
            {
                recordState = "RIN"; //Rejected
                authorizedBy.clear();
                Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por no activa");
            }
            return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+
                    currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','"+recordState+"','"+authorizedBy+"')";
        }
        else if(freq == 1)
        {
            if(startDate.daysTo(currentDate) < 0)
            {
                //Out of date range.
                qApp->beep();

                do
                    authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado, fuera de rango de fecha.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                while(ok && authorizedBy.isEmpty());

                if (ok)
                {
                    authorizedBy = "[OUT OF DATE RANGE]: " + authorizedBy;
                    Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                    recordState = "O";
                }
                else
                {
                    authorizedBy.clear();
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango de fecha");
                    recordState = "ROD";
                }
                return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
            }
            else if(startTime.secsTo(currentTime)< 0 || currentTime.secsTo(endTime) < 0)
            {
                //Out of time range.
                qApp->beep();

                do
                    authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                while(ok && authorizedBy.isEmpty());
                if (ok)
                {
                    authorizedBy = "[OUT OF TIME RANGE] " + authorizedBy;
                    Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                    recordState = "O";
                }
                else
                {
                    authorizedBy.clear();
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango horario");
                    recordState="ROT";
                }
                return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
            }
            else
            {
                return "insert into record (datetime_input,rut_people,rut_user,type,state,comment,patent_input,patent_output) values ('"
                        +currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"','"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','O','"
                        +ui->lineEdit_comment->text()+"','"+ui->lineEdit_patent_input->text()+"','"+ui->lineEdit_patent_output->text()+"')";
            }
        }
        else if(freq != 1)
        {
            if(startDate.daysTo(currentDate) < 0 || currentDate.daysTo(endDate) < 0)
            {
                //Out of date range.
                qApp->beep();

                do
                    authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para esta fecha.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                while(ok && authorizedBy.isEmpty());

                if (ok)
                {
                    authorizedBy = "[OUT OF DATE RANGE]: " + authorizedBy;
                    Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                    recordState = "O";
                }
                else
                {
                    authorizedBy.clear();
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango de fecha");
                    recordState = "ROD";
                }
                return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
            }
            else
            {
                if(startTime.secsTo(currentTime) < 0 || currentTime.secsTo(endTime) < 0)
                {
                    //Out of time range.
                    qApp->beep();

                    do
                        authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                    while(ok && authorizedBy.isEmpty());
                    if (ok)
                    {
                        authorizedBy = "[OUT OF TIME RANGE] " + authorizedBy;
                        Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                        recordState = "O";
                    }
                    else
                    {
                        authorizedBy.clear();
                        Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango horario");
                        recordState="ROT";
                    }
                    return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
                }
                else
                {
                    return "insert into record (datetime_input,rut_people,rut_user,type,state,comment,patent_input,patent_output) values ('"
                            +currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"','"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','O','"
                            +ui->lineEdit_comment->text()+"','"+ui->lineEdit_patent_input->text()+"','"+ui->lineEdit_patent_output->text()+"')";
                }

            }
        }
        else if(startDate.daysTo(currentDate) < 0 || currentDate.daysTo(endDate) < 0)
        {
            //Out of date range.
            qApp->beep();

            do
                authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para esta fecha.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
            while(ok && authorizedBy.isEmpty());

            if (ok)
            {
                authorizedBy = "[OUT OF DATE RANGE]: " + authorizedBy;
                Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" no autorizado ("+
                                      currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                recordState = "O";
            }
            else
            {
                authorizedBy.clear();
                Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango de fecha");
                recordState = "ROD";
            }
            return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+
                    currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','"+recordState+"','"+authorizedBy+"')";
        }
        else if(startTime.secsTo(currentTime)< 0 || currentTime.secsTo(endTime) < 0)
        {
            //Out of time range.
            qApp->beep();
            do
                authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
            while(ok && authorizedBy.isEmpty());
            if (ok)
            {
                authorizedBy = "[OUT OF TIME RANGE] " + authorizedBy;
                Logger::insert2Logger(rutSignin," DEBUG ", ui->lineEdit_rut->text() +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+
                                      "), fué autorizado por "+authorizedBy);
                recordState = "O";
            }
            else
            {
                authorizedBy.clear();
                Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+ui->lineEdit_rut->text()+" rechazada por intentar acceder fuera de rango horario");
                recordState="ROT";
            }
            return "insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+
                    " "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','"+recordState+"','"+authorizedBy+"')";
        }
        else
        {
            if(ui->lineEdit_profile->text().contains("CONTRATISTA"))
            {
                QString security = "true"; //For some reason not working with bool type. (pending)
                QString pension = "true";
                int satisfy = 0;
                if(ui->checkBox_security->isChecked())
                    if(ui->checkBox_pension->isChecked())
                        satisfy=1;
                    else
                    {
                        satisfy=0;
                        pension="false";
                    }
                else
                {
                    security="false";
                    satisfy=0;
                }
                QString authorizedBy;
                bool ok;
                if(satisfy==0)
                {
                    qApp->beep();
                    do
                        authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado por incumplimiento de obligaciones, solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                    while(ok && authorizedBy.isEmpty());
                    if (ok){
                        return "insert into record (datetime_input,rut_people,rut_user,type,state,comment,patent_input,patent_output,authorized_by,pension_quotes,security_elements) values ('"
                                +currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"','"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','O','"
                                +ui->lineEdit_comment->text()+"','"+ui->lineEdit_patent_input->text()+"','"+ui->lineEdit_patent_output->text()+"','"+authorizedBy+"','"+pension+"','"+security+"')";
                    }
                    else{
                        // creo que hay que limpiar
                    }
                }
                else
                {
                    return "insert into record (datetime_input,rut_people,rut_user,type,state,comment,patent_input,patent_output,pension_quotes,security_elements) values ('"
                            +currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"','"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','O','"
                            +ui->lineEdit_comment->text()+"','"+ui->lineEdit_patent_input->text()+"','"+ui->lineEdit_patent_output->text()+"','"+pension+"','"+security+"')";
                }
            }
            else
            {
                return "insert into record (datetime_input,rut_people,rut_user,type,state,comment,patent_input,patent_output) values ('"
                        +currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"','"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','O','"
                        +ui->lineEdit_comment->text()+"','"+ui->lineEdit_patent_input->text()+"','"+ui->lineEdit_patent_output->text()+"')";
            }
        }
    }
}

void ReadWithoutCI::on_pushButton_register_clicked()
{
    if(!ui->lineEdit_names->text().isEmpty())
    {
        connection conn;
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        int inputCurrentIndex = ui->listView_imput->currentIndex().row();
        qDebug()<<hasInput;
        if(hasInput)
        {
            if(inputCurrentIndex < 0)
            {
                QMessageBox::warning(this,tr("Advertencia"),tr("Este usuario contiene registros de entrada sin salida, favor registrar salida manual antes de continuar."));
                ui->listView_imput->setFocus();
                qDebug()<<ui->listView_imput->currentIndex();
                //ui->listView_imput->setCurrentIndex(ui->listView_imput->model()->index(0,0));
                QModelIndex Index= ui->listView_imput->model()->index(0,0);
                ui->listView_imput->selectionModel()->select( Index, QItemSelectionModel::Select );
                Logger::insert2Logger(rutSignin," ERROR ", "Se ha intentado registrar entrada del usuario " +ui->lineEdit_rut->text()+" que contiene ingresos previos.");

            }
            else{
                if(ui->lineEdit_comment->text().isEmpty())
                    qry->prepare("update record set state='C',datetime_output='"+currentDateTime.toString("yyyy-MM-dd HH:mm")+"',patent_output='"+
                                 ui->lineEdit_patent_output->text()+"' where datetime_input='"+
                                 ui->listView_imput->currentIndex().data().toString()+"' and rut_people='"+ui->lineEdit_rut->text()+"'");
                else
                    qry->prepare("update record set state='C',datetime_output='"+currentDateTime.toString("yyyy-MM-dd HH:mm")+"',patent_output='"+
                                 ui->lineEdit_patent_output->text()+"',comment=comment ||', "+ui->lineEdit_comment->text()+"' where datetime_input='"+
                                 ui->listView_imput->currentIndex().data().toString()+"' and rut_people='"+ui->lineEdit_rut->text()+"'");
            }
        }else
            qry->prepare(verifyPeople());

        // QSqlQueryModel *modal=new QSqlQueryModel();
        // ui->listView_imput->setCurrentIndex(modal->index(0,0));

        if(qry->exec())
        {

            Logger::insert2Logger(rutSignin, " DEBUG ", ui->lineEdit_rut->text() + " -> " + qry->lastQuery());
            QMessageBox::information(this,tr("ENHORABUENA"),tr("Persona registrado exitosamente."));
            clean();
        }
        else
        {
            qApp->beep();
            QMessageBox::critical(this,tr("Error al registrar"),error1);
            Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
        }

        delete qry;
    }
    else
    {
        qApp->beep();
        QMessageBox::warning(this,tr("Error al registrar"),tr("Realice busqueda por rut primero."));
        ui->lineEdit_rut->setFocus();
    }
}

void ReadWithoutCI::on_pushButton_3_clicked()
{
    ReadWithoutCI::close();
}

void ReadWithoutCI::on_lineEdit_rut_editingFinished()
{
    QString rut = ui->lineEdit_rut->text();
    rut.replace("-", "");
    rut.replace(".","");
    rut.toUpper(); // for k
    ui->lineEdit_rut->setText(rut);
}

void ReadWithoutCI::clean()
{
    ui->lineEdit_rut->clear();
    ui->lineEdit_names->clear();
    ui->lineEdit_maternal_surname->clear();
    ui->lineEdit_paternal_surname->clear();
    ui->lineEdit_patent_input->clear();
    ui->lineEdit_patent_output->clear();
    ui->lineEdit_comment->clear();
    ui->lineEdit_company->clear();
    ui->lineEdit_rut->setFocus();

    QPixmap user(":images/User-blue-icon.png");
    ui->label_user->setPixmap(user);

    QSqlQueryModel *modal=new QSqlQueryModel();
    ui->listView_imput->setModel(modal);
    ui->listView_imput->setEnabled(false);

    ui->lineEdit_patent_output->setEnabled(false);
    ui->lineEdit_profile->clear();
    ui->lineEdit_patent_input->setEnabled(false);
    ui->lineEdit_comment->setEnabled(false);
    ui->checkBox_pension->setChecked(false);
    ui->checkBox_security->setChecked(false);
    ui->checkBox_pension->setEnabled(false);
    ui->checkBox_security->setEnabled(false);
}

void ReadWithoutCI::on_listView_imput_clicked()
{
    ui->lineEdit_patent_input->setEnabled(false);
}

void ReadWithoutCI::on_lineEdit_patent_output_editingFinished()
{
    ui->lineEdit_patent_output->setText(ui->lineEdit_patent_output->text().toUpper());
}

void ReadWithoutCI::on_lineEdit_patent_input_editingFinished()
{
    //ui->lineEdit_patent_input->setText(ui->lineEdit_patent_input->text().toUpper());
}

void ReadWithoutCI::on_lineEdit_comment_editingFinished()
{
    ui->lineEdit_comment->setText(ui->lineEdit_comment->text().toUpper());
}

void ReadWithoutCI::on_lineEdit_patent_input_textChanged(const QString &arg1)
{
    ui->lineEdit_patent_input->setText(ui->lineEdit_patent_input->text().toUpper());
}
