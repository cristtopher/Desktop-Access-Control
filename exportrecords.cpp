#include "exportrecords.h"
#include "ui_exportrecords.h"

#include "connection.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QAxObject>
#include "xlsxdocument.h"

#include <QProgressDialog>

QString fileName;
QString path;

ExportRecords::ExportRecords(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportRecords)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Exportar");

    ui->lineEdit->setText(QDir::homePath()+"/"+QStandardPaths::displayName(QStandardPaths::DesktopLocation)+"/Reporte.xls");
    ui->calendarWidget->setMaximumDate(QDate::currentDate());
    ui->calendarWidget_2->setMaximumDate(QDate::currentDate());
    ui->timeEdit_2->setTime(QTime::fromString("23:59"));
}

ExportRecords::~ExportRecords()
{
    delete ui;
}

void ExportRecords::on_toolButton_clicked()
{
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"C:/",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!path.isNull()){
        fileName = "Reporte.xlsx";
        ui->lineEdit->setText(path+"/"+fileName);
    }
}

void ExportRecords::on_pushButton_clicked()
{
    QString startDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QString endDate = ui->calendarWidget_2->selectedDate().toString("yyyy-MM-dd");
    QString startHour = ui->timeEdit->time().toString("H:mm");
    QString endHour = ui->timeEdit_2->time().toString("H:mm");

    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(!qry->exec("select r.id,r.state,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,p.birthdate,na.name,p.cellphone,c.name,pro.name,po.name,fr.name,p.start_authorized_date,p.end_authorized_date,p.start_authorized_hour,p.end_authorized_hour,r.type,r.datetime_input,r.datetime_output,r.patent_input,r.patent_output,us.names,r.authorized_by,r.comment from record as r left join people as p on r.rut_people=p.rut left join nationality as na on p.code_nationality=na.code left join company as c on p.rut_company=c.rut left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as fr on p.id_frequency=fr.id inner join user as us on r.rut_user=us.rut where r.datetime_input between '"+startDate+" "+startHour+"' and '"+endDate+" "+endHour+"'"))
    {
        qApp->beep();
        QMessageBox::critical(this,tr("Error:"), qry->lastError().text());
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text());
    }
    else
    {
        QXlsx::Document xlsx;
        //img
        //xlsx.insertImage(1,1,QImage::QImage("D:\ComboScan\images\logo.png"));

        // Format header
        QXlsx::Format fontBold;
        fontBold.setFontBold(true);
        fontBold.setFontSize(12);
        //fontBold.setPatternBackgroundColor(QColor::QColor(206,224,255));

        //property
        xlsx.setDocumentProperty("title", "Report records");
        xlsx.setDocumentProperty("creator", "Access Control software");
        xlsx.setDocumentProperty("company", "AXXEZO S.A");
        xlsx.setDocumentProperty("category", "Spreadsheets Report");
        xlsx.setDocumentProperty("description", "Report records the date and time range");

        //Width
        xlsx.setColumnWidth(1,1,6.0);
        xlsx.setColumnWidth(3,3,10.0);
        xlsx.setColumnWidth(4,4,16.0);
        xlsx.setColumnWidth(5,5,16.0);
        xlsx.setColumnWidth(6,6,16.0);
        xlsx.setColumnWidth(7,7,14.0);
        xlsx.setColumnWidth(8,8,16.0);
        xlsx.setColumnWidth(9,9,11.0);
        xlsx.setColumnWidth(10,10,20.0);
        xlsx.setColumnWidth(11,11,30.0);
        xlsx.setColumnWidth(12,12,45.0);
        xlsx.setColumnWidth(13,13,13.0);
        xlsx.setColumnWidth(14,14,17.0);
        xlsx.setColumnWidth(15,15,17.0);
        xlsx.setColumnWidth(16,16,17.0);
        xlsx.setColumnWidth(17,17,17.0);
        xlsx.setColumnWidth(18,18,17.0);
        xlsx.setColumnWidth(19,19,17.0);
        xlsx.setColumnWidth(20,20,15.0);
        xlsx.setColumnWidth(21,21,17.0);
        xlsx.setColumnWidth(22,22,15.0);
        xlsx.setColumnWidth(23,23,20.0);
        xlsx.setColumnWidth(24,24,18.0);
        xlsx.setColumnWidth(25,25,20.0);
        xlsx.setColumnWidth(26,26,35.0);
        xlsx.setColumnWidth(27,27,40.0);
        xlsx.setColumnWidth(28,28,50.0);

        // Estadistics
        //qDebug()<<"select count(p.rut) from record as r left join people as p on r.rut_people=p.rut where p.id_profile=16 and r.datetime_input between '"+startDate+" "+startHour+"' and '"+endDate+" "+endHour+"'";
        //xlsx.write(1,1, "PROVEEDORES: ",fontBold);
        //xlsx.write(1,2,conn.getFirstFromDb(rutSignin,"select count(p.rut) from record as r left join people as p on r.rut_people=p.rut where p.id_profile=16 and r.datetime_input between '"+startDate+" "+startHour+"' and '"+endDate+" "+endHour+"' and r.state='C'"));


        // Titles Header
        xlsx.write(1,1,"ID",fontBold);
        xlsx.write(1,2,"ESTADO",fontBold);
        xlsx.write(1,3,"RUT",fontBold);
        xlsx.write(1,4,"NOMBRES",fontBold);
        xlsx.write(1,5,"AP. PATERNO",fontBold);
        xlsx.write(1,6,"AP. MATERNO",fontBold);
        xlsx.write(1,7,"CUMPLEAÑOS",fontBold);
        xlsx.write(1,8,"NACIONALIDAD",fontBold);
        xlsx.write(1,9,"TELEFONO",fontBold);
        xlsx.write(1,10,"EMPRESA",fontBold);
        xlsx.write(1,11,"PERFIL",fontBold);
        xlsx.write(1,12,"CARGO",fontBold);
        xlsx.write(1,13,"FRECUENCIA",fontBold);
        xlsx.write(1,14,"INICIO FECH AUT",fontBold);
        xlsx.write(1,15,"FIN FECH AUT",fontBold);
        xlsx.write(1,16,"INICIO HORA AUT",fontBold);
        xlsx.write(1,17,"FIN HORA AUT",fontBold);
        xlsx.write(1,18,"TIPO",fontBold);
        xlsx.write(1,19,"FECHA ENTRADA",fontBold);
        xlsx.write(1,20,"FECHA SALIDA",fontBold);
        xlsx.write(1,21,"HORA ENTRADA",fontBold);
        xlsx.write(1,22,"HORA SALIDA",fontBold);
        xlsx.write(1,23,"PATENTE ENTRADA",fontBold);
        xlsx.write(1,24,"PATENTE SALIDA",fontBold);
        xlsx.write(1,25,"OPERARIO",fontBold);
        xlsx.write(1,26,"AUTORIZADO POR",fontBold);
        xlsx.write(1,27,"RAZON",fontBold);
        xlsx.write(1,28,"COMENTARIO",fontBold);

        int row=2;
        QString state;
        QString type;
        while(qry->next())
        {
            xlsx.write(row,1, qry->value(ID)); //ID

            if(qry->value(STATE).toString()=="O")
                state = "ABIERTO";
            else if(qry->value(STATE).toString()=="C")
                state = "CERRADO";
            else if(qry->value(STATE).toString()=="RIN")
                state = "RECHAZADO POR INACTIVO";
            else if(qry->value(STATE).toString()=="ROD")
                state = "RECHAZADO POR FUERA DE RANGO FECHA";
            else if(qry->value(STATE).toString()=="ROT")
                state = "RECHAZADO POR FUERA DE RANGO HORA";
            else if(qry->value(STATE).toString()=="R")
                state = "RECHAZADO";
            else if(qry->value(STATE).toString()=="RDB")
                state = "RECHAZADO POR NO REGISTRADO";
            else if(qry->value(STATE).toString()=="RMR")
                state = "RECHAZADO POR NO CUMPLIR REQUERIMIENTOS SUBCONTRATISTA";
            else if(qry->value(STATE).toString()=="RNQ")
                state = "RECHAZADO POR NO CUMPLIR REQUERIMIENTOS PREVISIONALES DE SUBCONTRATISTA";
            else if(qry->value(STATE).toString()=="RNS")
                state = "RECHAZADO POR NO CUMPLIR REQUERIMIENTOS SEGURIDAD PARA SUBCONTRATISTA";
            else if(qry->value(STATE).toString()=="E")
                state = "ENROLAMIENTO";

            xlsx.write(row,2, state); //estado
            xlsx.write(row,3, qry->value(RUT_PEOPLE).toString().toUpper()); //rut
            xlsx.write(row,4, qry->value(NAMES).toString()); //nombres
            xlsx.write(row,5, qry->value(PATERNAL_SURNAME).toString()); //ap paterno
            xlsx.write(row,6, qry->value(MATERNAL_SURNAME).toString()); //ap materno
            xlsx.write(row,7, QDate::fromString(qry->value(BIRTHDATE).toString(),"yyyy-MM-dd"));
            xlsx.write(row,8, qry->value(NATIONALITY).toString());
            xlsx.write(row,9, qry->value(CELLPHONE));
            xlsx.write(row,10, qry->value(COMPANY).toString()); //empresa
            xlsx.write(row,11, qry->value(PROFILE).toString()); //perfil
            xlsx.write(row,12, qry->value(POSITION).toString()); //cargo
            xlsx.write(row,13, qry->value(FREQUENCY).toString()); //frecuencia
            xlsx.write(row,14, QDate::fromString(qry->value(START_AUTHORIZED_DATE).toString(),"yyyy-MM-dd")); //inicio fecha autorizacion
            xlsx.write(row,15, QDate::fromString(qry->value(END_AUTHORIZED_DATE).toString(),"yyyy-MM-dd")); //fin fecha autorizacion
            xlsx.write(row,16, QTime::fromString(qry->value(START_AUTHORIZED_HOUR).toString(),"H:m")); //inicio hora autorizacion
            xlsx.write(row,17, QTime::fromString(qry->value(END_AUTHORIZED_HOUR).toString(),"H:m")); //fin hora autorizacion

            if(qry->value(TYPE).toString()=="A")
                type = "AUTOMATICO";
            else
                type = "MANUAL";
           
			 //split of datetime imput
            QString dateTimeImput=qry->value(DATETIME_INPUT).toString();
            QStringList dateTimeInputSplit=dateTimeImput.split(" ");
            //split of datetime output
            QString dateTimeOutput=qry->value(DATETIME_OUTPUT).toString();
            QStringList dateTimeOutputSplit=dateTimeOutput.split(" ");
            //QDateTime::fromString(qry->value(DATETIME_OUTPUT).toString(),"yyyy-MM-dd HH:mm")

           xlsx.write(row,18, type); //Type
            xlsx.write(row,19, dateTimeInputSplit.value(0)); //fecha entrada
            xlsx.write(row,20, dateTimeOutputSplit.value(0)); //fecha salida
            xlsx.write(row,21, dateTimeInputSplit.value(1)); //hora entrada
            xlsx.write(row,22, dateTimeOutputSplit.value(1)); //hora salida
            xlsx.write(row,23, qry->value(PATENT_INPUT).toString()); //patente entrada
            xlsx.write(row,24, qry->value(PATENT_OUTPUT).toString()); //patente salida
            xlsx.write(row,25, qry->value(USUARIO).toString()); //operario
            //split the authorized_by in two fields
            QString fullAuthorizer=qry->value(AUTHORIZED_BY).toString();
            QStringList splitReason=fullAuthorizer.split(':');
            xlsx.write(row,26,splitReason.value(1)); //Authorized By
            if(splitReason.value(0)=="[OUT OF TIME RANGE]")
                xlsx.write(row,27,"[RECHAZADO POR FUERA DE RANGO HORA]");
            else
                if(splitReason.value(0)=="[OUT OF DATE RANGE]")
                    xlsx.write(row,27,"[RECHAZADO POR FUERA DE RANGO FECHA]");
                else
                    xlsx.write(row,27,splitReason.value(0)); //Reason
            state.clear();
            xlsx.write(row,28, qry->value(COMMENT).toString()); //comentario
            row++;
        }
        if(row==2)
        { // equals to default value.
            QMessageBox::warning(this,tr("ADVERTENCIA"),tr("No hay registros en este rango de fecha"));
        }
        else
        {
            xlsx.saveAs(ui->lineEdit->text());
            QMessageBox::information(this,tr("Enorabuena"),tr("Archivo generado exitosamente."));
        }

    delete qry;
    }
}

void ExportRecords::on_pushButton_2_clicked()
{
    this->close();
}
