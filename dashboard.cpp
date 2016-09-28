#include "dashboard.h"
#include "ui_dashboard.h"

#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QInputDialog>
#include <QFileDialog>
#include <QCheckBox>
#include <QProgressBar>
#include <QSound>
#include <QSerialPort>
#include <QFile>

#include "connection.h"
#include "login.h"
#include "exportrecords.h"
#include "readwithoutci.h"
#include "people.h"
#include "logger.h"
#include "users.h"
#include "logger.h"
#include "companies.h"
#include "userprofile.h"
#include "individualreport.h"
#include "rejectedreport.h"
#include "configuration.h"
#include "dailyreport.h"
#include "formcs.h"
#include <login.h>
#include <administratormenu.h>

#include <QtCore>
#include "xlsxdocument.h"

//Necesary for PR
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "include/prapi.h"
#include "include/gxsd.h"
#include "include/gxsdldr.cpp"
#include "__lib__.h"

#include <iomanip>

#include <QProgressDialog>
#include <QtWidgets/QApplication>

bool loginWindow;

Lib lib;

#ifdef GX_NAMESPACES
using namespace gx; //jdk
using namespace pr; //API
#endif
using namespace std;

QString global_PERSONAL_DATA; //rut.
QString global_GIVENNAME;
QString global_MATERNAL_SURNAME;
QString global_PATERNAL_SURNAME;
QString global_BIRTH_DATE;
QString global_CODE_NATIONALITY;
QString global_NATIONALITY;
QString global_DOCUMENT_NUMBER;
QString global_TYPE;
QString global_COMPANY;
QString global_PROFILE;
QString global_POSITION;
QString global_STATE;
QString global_START_AUTHORIZED_HOUR;
QString global_END_AUTHORIZED_HOUR;
QString global_START_AUTHORIZED_DATE;
QString global_END_AUTHORIZED_DATE;
QString global_PICTURE;
QString global_DATETIME_INPUT; //used for rejecting access.
//form
QString global_FREQUENCY;
QString PERSONAL_DATA;
QString GIVENNAME;
QString MATERNAL_SUR;
QString PATERNAL_SUR;
QString codeAdministration;


PassportReader pr;  /* Object for the PR system */
QSerialPort *RTScan; /* Object for the RTscan */
connection conn;
Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    QPixmap okPix(":/images/ok.png");
    QPixmap badPix(":/images/bad.png");
    QPixmap userBlueIcon(":/images/User-blue-icon.png");
    QPixmap LogoPix(":/images/axxezo.png");
    QPixmap userProfilePix(":/images/user.png");
    //conn.connOpen();
    qDebug ()<<conn.mydb.isOpen();
    if(conn.isOpenDB())
        ui->label_status_db->setPixmap(okPix);
    else
        ui->label_status_db->setPixmap(badPix);

    if(rutSignin.isEmpty())
        on_actionSalir_triggered();

    ui->label_user->setPixmap(userBlueIcon);

    if(comboScanIsOpen())
        ui->label_status_cs->setPixmap(okPix);
    else
    {
        ui->label_status_cs->setPixmap(badPix);
        Logger::insert2Logger(rutSignin," ERROR ", "ComboScan desconectado.");
    }

    this->setWindowTitle("Control de accesos - Patagonia Wings");
    QPixmap deniedPix(":images/Access-Denied-icon.png");
    QIcon DeniedIcon(deniedPix);
    QIcon userProfileIcon(userProfilePix);
    ui->pushButton_rejected->setIcon(DeniedIcon);
    ui->pushButton_userProfile->setIcon(userProfileIcon);

    ui->label_userName->setText(conn.getFirstFromDb(rutSignin,"select names from users where rut='"+rutSignin+"'"));

    QTimer *timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();

    //loading record head for filtered by combobox
    ui->comboBox_filtered->addItem("Rut","rut");
    ui->comboBox_filtered->addItem("Nombres","names");
    ui->comboBox_filtered->addItem("Apellido Paterno","paternal_surname");
    ui->comboBox_filtered->addItem("Apellido Materno","maternal_surname");
    ui->comboBox_filtered->addItem("Patente Entrada","patent_input");

    // Set permissions
    ui->actionAdministrarEmpresas->setEnabled(true);
    ui->actionAdministrarCargos->setEnabled(false);
    ui->actionAdministrarPerfiles->setEnabled(false);
    switch (conn.getFirstFromDb(rutSignin,"select id_rol from users where rut='"+rutSignin+"'").toInt()) {
    case 2: //Authorizer
        ui->menuEmpresas->setEnabled(false);
        ui->menuCargos->setEnabled(false);
        ui->menuPerfiles->setEnabled(false);
        ui->menuUsuarios->setEnabled(false);
        ui->actionActualizar->setEnabled(false);
        ui->actionExportar->setEnabled(false);
        ui->menuHerramientas->setEnabled(false);
        ui->menuReportes->setEnabled(false);
        break;
    case 3: //Administrator
        //ui->menuUsuarios->setEnabled(true);
        break;
    case 1: //Operator
        ui->menuDatos->setEnabled(false);
        ui->actionExportar->setEnabled(false);
        ui->actionConfiguraci_n->setEnabled(false);
        ui->menuReportes->setEnabled(false);
        break;
    case 4: //Supervisor
        ui->actionExportar->setEnabled(false);
        ui->actionConfiguraci_n->setEnabled(false);
        ui->menuReportes->setEnabled(false);
        ui->menuEmpresas->setEnabled(false);
        ui->menuCargos->setEnabled(false);
        ui->menuPerfiles->setEnabled(false);
        ui->menuUsuarios->setEnabled(false);
        ui->actionImportarPersonas->setEnabled(false);
        break;
    default:
        break;
    }

    QString query;
    if(ui->tabWidget->currentIndex()==0) //For input table
        query = "default_input"; //query it's on loadtables function
    else if(ui->tabWidget->currentIndex()==1)
        query = "default_output";
    else if(ui->tabWidget->currentIndex()==2)
        query = "default_rejected";

    BuildTables();
    loadTables(query);

    ui->lineEdit_pdf417->setFocus();
    //loopComboScan();

    //RTScan
    RTScan = new QSerialPort(this);
    RTScan->setPortName(conn.getFirstFromDb(rutSignin,"select rtscan_port from configuration where key=(select key from users where rut = '"+rutSignin+"')"));
    qDebug()<<conn.getFirstFromDb(rutSignin,"select rtscan_port from configuration where key=(select key from users where rut = '"+rutSignin+"')");
    if(RTScan->open(QIODevice::ReadOnly))
    {
        RTScan->setBaudRate(QSerialPort::Baud115200);
        RTScan->setDataBits(QSerialPort::Data8);
        RTScan->setParity(QSerialPort::NoParity);
        RTScan->setStopBits(QSerialPort::OneStop);
        RTScan->setFlowControl(QSerialPort::NoFlowControl);
        ui->label_status_lect->setPixmap(okPix);
        connect(RTScan, SIGNAL(readyRead()),this,SLOT(serialReceived()));
        qDebug()<<RTScan->isOpen();
    }
    else
    {
        ui->label_status_lect->setPixmap(badPix);
        Logger::insert2Logger(rutSignin," ERROR ", "RTScan desconectado.");
        qDebug()<<RTScan->isOpen();
    }
    // QString imgPath = QDir::currentPath()+"/people/" + rut + ".jpg";
    if(!QDir("people").exists())
        QDir().mkdir("people");

}

void Dashboard::loopComboScan(){
    vector<string> statxt(6);
    statxt[0] = "No document detected.";
    statxt[1] = "Document is moving.";
    statxt[2] = "Take out the document!";
    statxt[3] = "";
    statxt[4] = "Ready for reading.";
    statxt[5] = "Button is pressed.";

    try {
        /* Opening the PR system */
        lib.FunctionStart("Opening system files");
        PassportReader pr;  /* Object for the PR system */
        lib.FunctionEnd();

        /* Validity check */
        if (!pr.IsValid()) {
            lib.Error("Failed to initialize!");
        }

        /* Connecting to the first device */
        lib.FunctionStart("Connecting to the first device");
        pr.UseDevice(0,PR_UMODE_FULL_CONTROL);
        lib.FunctionEnd();

        /* Enabling motion detection */
        try {
            lib.FunctionStart("Enabling motion detection");
            pr.SetProperty("freerun_mode",PR_FRMODE_TESTDOCUMENT);
            lib.FunctionEnd();
        } catch (gxException e) {
            lib.DisplExcp(e);
        }

        while (!lib.KbHit()) {
            try {
                /* Testing the start button */
                int state = pr.TestButton(PR_KEY_START);
                if (state == PR_KEY_PRESSED) state = 5;
                else {
                    /* If the start button is not pressed testing the document detection */
                    state = pr.TestDocument(0);

                    /* Turning the display leds depending on the status */
                    int color = PR_SLC_OFF;
                    switch(state) {
                    case PR_TD_OUT:     color = PR_SLC_GREEN; break;
                    case PR_TD_MOVE:    color = PR_SLC_ANY; break;
                    case PR_TD_NOMOVE:  color = PR_SLC_RED; break;
                    }
                    pr.SetStatusLed(0xFF, color);
                }
                lib.Write("State of the device: " + statxt[state] + "        \r");
                if(state  == 4){
                    readFromPR();
                }
                lib.Wait(200);
                if ((state == PR_TD_IN) || (state == 5)){
                    //readFromPR();
                    lib.Wait(800);
                }
            } catch (gxException e) {
                lib.DisplExcp(e);
            }
        }
        lib.WriteLine("");

        /* Turning off the lights */
        try {
            lib.FunctionStart("Turning off the lights");
            pr.SetProperty("freerun_mode", PR_FRMODE_NULL);
            lib.FunctionEnd();
        } catch (gxException e) {
            lib.DisplExcp(e);
        }

        /* Turning off the display leds */
        try {
            lib.FunctionStart("Turning off the display leds");
            pr.SetStatusLed(0xFF, PR_SLC_OFF);
            lib.FunctionEnd();
        } catch (gxException e) {
            lib.DisplExcp(e);
        }

        /* Closing the device */
        lib.FunctionStart("Closing the device");
        pr.CloseDevice();
        lib.FunctionEnd();

    } catch (gxException e) {
        lib.DisplExcp(e);
    }
}

bool Dashboard::comboScanIsOpen(){
    try
    {
        gxDeviceInfo filter;
        vector<gxDeviceInfo> devices = gxSystem::ListDevices(0, filter);

        if(devices.size() == 0) {
            wcout << L"No GX devices." << endl;
            return false;
        }

        wcout << L"GX devices in the system:\n";
        for(size_t i = 0; i < devices.size(); i++) {
            wcout << i+1 << L". Name: " << devices[i].GetName() << \
                     L", Type: " << devices[i].GetType() << \
                     L", Serial: " << devices[i].GetSerial() << \
                     L", Prio: " << devices[i].GetPriority() << endl;
            qDebug()<<devices[i].GetSerial();
        }
        wcout << L"Found " << devices.size() << L" devices." << endl;
        return true;

    }
    catch(gxException &e)
    {
        wcerr << L"Error (0x" << hex << setw(8) << setfill(L'0') << \
                 e.GetErrorCode() << L"): " << e.GetErrorString() << endl;
        return false;
    }
}

void Dashboard::BuildTables()
{
    QStringList header;
    header <<"ID" << "Fecha ingreso" << "Rut" << "Nombres" << "Ap. Paterno" << "Ap. Materno" << "Empresa" << "Perfil" << "Patente Entr." << "Comentario";
    ui->tableWidget_input->setColumnCount(header.size());
    ui->tableWidget_input->setHorizontalHeaderLabels(header);
    ui->tableWidget_input->hideColumn(0);
    ui->tableWidget_input->setColumnWidth(1,95); //datetime_input
    ui->tableWidget_input->setColumnWidth(2,65); //rut
    ui->tableWidget_input->setColumnWidth(3,105); //nombres
    ui->tableWidget_input->setColumnWidth(4,85); //ap. paterno
    ui->tableWidget_input->setColumnWidth(5,85); //ap. materno
    ui->tableWidget_input->setColumnWidth(6,164); //empresa
    ui->tableWidget_input->setColumnWidth(7,170); //perfil
    ui->tableWidget_input->setColumnWidth(8,80); //patente entr.
    ui->tableWidget_input->setColumnWidth(9,200); //comentario

    //desabilitar edicion en columnas (excepto las de patentes y comentario)

    header.clear();
    header <<"ID" << "Fecha ingreso" << "Rut" << "Nombres" << "Ap. Paterno" << "Ap. Materno" << "Empresa" << "Perfil" << "Patente Entr." << "Patente Salid." << "Fecha salida" << "Comentario";
    ui->tableWidget_output->setColumnCount(header.size());
    ui->tableWidget_output->setHorizontalHeaderLabels(header);
    ui->tableWidget_output->hideColumn(0);
    ui->tableWidget_output->setColumnWidth(1,95); //Input date
    ui->tableWidget_output->setColumnWidth(2,65); //Rut
    ui->tableWidget_output->setColumnWidth(3,105); //Names
    ui->tableWidget_output->setColumnWidth(4,85); //Paternal surname
    ui->tableWidget_output->setColumnWidth(5,85); //Maternal surname
    ui->tableWidget_output->setColumnWidth(6,164); //Company
    ui->tableWidget_output->setColumnWidth(7,170); //Profile
    ui->tableWidget_output->setColumnWidth(8,80); //Patent input
    ui->tableWidget_output->setColumnWidth(9,80); //Patent output
    ui->tableWidget_output->setColumnWidth(10,95); //Datetime output
    ui->tableWidget_output->setColumnWidth(11,200); //Comment

    header.clear();
    header <<"ID" << "Fecha rechazo" << "Rut" << "Nombres" << "Ap. Paterno" << "Ap. Materno" << "Empresa" << "Perfil" << "Motivo" << "Patente" << "Comentario";
    ui->tableWidget_rejected->setColumnCount(header.size());
    ui->tableWidget_rejected->setHorizontalHeaderLabels(header);
    ui->tableWidget_rejected->hideColumn(0);
    ui->tableWidget_rejected->setColumnWidth(1,95); //datetime_rejected
    ui->tableWidget_rejected->setColumnWidth(2,65); //rut
    ui->tableWidget_rejected->setColumnWidth(3,105); //nombres
    ui->tableWidget_rejected->setColumnWidth(4,85); //ap. paterno
    ui->tableWidget_rejected->setColumnWidth(5,85); //ap. materno
    ui->tableWidget_rejected->setColumnWidth(6,164); //empresa
    ui->tableWidget_rejected->setColumnWidth(7,170); //perfil
    ui->tableWidget_rejected->setColumnWidth(8,60); //motivo
    ui->tableWidget_rejected->setColumnWidth(9,80); //patente entr.
    ui->tableWidget_rejected->setColumnWidth(10,200); //comentario

}

void Dashboard::loadTables(QString type)
{
    clean("O",false);
    clean("C",false);
    clean("R",false);
    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString query;
    //    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    if(type == "default_input")
        query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.comment,p.picture,pos.name from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id left join position as pos on pos.id=p.id_position  where r.state='O' and r.datetime_input like '"+currentDate+"%' order by datetime_input";
    else if(type == "default_output")
        query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.patent_output,r.datetime_output,r.comment,p.picture,pos.name from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id left join position as pos on pos.id=p.id_position where r.state='C' and r.datetime_output like '"+currentDate+"%' order by datetime_output";
    else if(type == "default_rejected")
        query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.state,r.patent_input,r.comment,p.picture,pos.name from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id left join position as pos on pos.id=p.id_position where r.state like 'R%' and r.datetime_input like '"+currentDate+"%' order by datetime_input";
    else
        query = type; // for no default querys.

    //    qry->prepare();
    if(!qry->exec(query))
    {
        QMessageBox::critical(this,tr("Error:"),error1);
        statusBar()->showMessage(error1,5000);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());

    }
    else
    {
        int row;
        QPixmap user;
        while(qry->next())
        {
            global_DATETIME_INPUT = qry->value(1).toString();
            ui->lineEdit_rut->setText(qry->value(2).toString());
            ui->lineEdit_name->setText(qry->value(3).toString());
            ui->lineEdit_paternalSurname->setText(qry->value(4).toString());
            ui->lineEdit_maternalSurname->setText(qry->value(5).toString());
            ui->lineEdit_company->setText(qry->value(6).toString());
            ui->lineEdit_profile->setText(qry->value(7).toString());
            if(ui->tabWidget->currentIndex()==0){
                ui->lineEdit_position->setText(qry->value(11).toString());
            }else if(ui->tabWidget->currentIndex()==1){
                ui->lineEdit_position->setText(qry->value(13).toString());
            }else if(ui->tabWidget->currentIndex()==2){
                ui->lineEdit_position->setText(qry->value(12).toString());
            }
            if(ui->tabWidget->currentIndex()==0) // Tab for input
            {
                row = ui->tableWidget_input->rowCount();
                // Inserts an empty row into the table at row.
                ui->tableWidget_input->insertRow(row);

                for(int column=0;column<=10;++column)
                    ui->tableWidget_input->setItem(row, column, new QTableWidgetItem(qry->value(column).toString()));

                //Picture
                if(!qry->value(10).toString().isEmpty())
                    user.load(qry->value(10).toString());
                else
                    user.load(":/images/User-blue-icon.png");
            }
            else if(ui->tabWidget->currentIndex()==1)// Tab for output
            {
                row = ui->tableWidget_output->rowCount();
                // Inserts an empty row into the table at row.
                ui->tableWidget_output->insertRow(row);

                for(int column=0;column<=12;++column){
                    ui->tableWidget_output->setItem(row, column, new QTableWidgetItem(qry->value(column).toString()));
                }

                //Picture
                if(!qry->value(12).toString().isEmpty())//valor anterior 11
                    user.load(qry->value(12).toString());//valor anterior 11
                else
                    user.load(":/images/User-blue-icon.png");
            }
            else if(ui->tabWidget->currentIndex()==2) // Tab for rejected
            {
                row = ui->tableWidget_rejected->rowCount();
                // Inserts an empty row into the table at row.
                ui->tableWidget_rejected->insertRow(row);

                for(int column=0;column<=11;++column){
                    if(column!=8)
                        ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem(qry->value(column).toString()));
                    else{
                        if(qry->value(column).toString()=="RIN")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("Inactivo"));
                        else if(qry->value(column).toString()=="ROD")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("Fuera fecha permitida"));
                        else if(qry->value(column).toString()=="ROT")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("Fuera horario permitido"));
                        else if(qry->value(column).toString()=="RDB")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("No está en DB"));
                        else if(qry->value(column).toString()=="RMR")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("No cumple req. subcontr"));
                        else if(qry->value(column).toString()=="RNQ")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("No cumple req. previsionales"));
                        else if(qry->value(column).toString()=="RNS")
                            ui->tableWidget_rejected->setItem(row, column, new QTableWidgetItem("No cumple req. seguridad"));
                    }
                }

                //Picture
                if(!qry->value(11).toString().isEmpty())
                    user.load(qry->value(11).toString());
                else
                    user.load(":/images/User-blue-icon.png");
            }
            ui->label_user->setPixmap(user);
        }
    }
    loadLCD();
    delete qry;
}

void Dashboard::on_lineEdit_filtered_textChanged(const QString &arg1)
{
    QString query;
    //for after deleting all.
    if(arg1.isEmpty())
    {
        if(ui->tabWidget->currentIndex()==0)
            query = "default_input";
        else if(ui->tabWidget->currentIndex()==1)
            query = "default_output";
        else if(ui->tabWidget->currentIndex()==2)
            query = "default_rejected";
    }
    else
    {
        int indexSelected = ui->comboBox_filtered->currentIndex();
        QString table;
        QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
        switch(indexSelected)
        {
        case 0: //rut
        case 1: //names
        case 2: //paternal_surname
        case 3: //maternal_surname
        case 4: //patent_input
            if(indexSelected==4)
                table="r";
            else
                table="p";
            if(ui->tabWidget->currentIndex()==0)
                query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.comment,p.picture from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id where r.state='O' and "+table+"."+ui->comboBox_filtered->itemData(indexSelected).toString()+" like '"+arg1+"%' and r.datetime_input like '"+currentDate+"%'";
            else if(ui->tabWidget->currentIndex()==1)
                query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.patent_output,r.datetime_output,r.comment,p.picture from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id where r.state='C' and "+table+"."+ui->comboBox_filtered->itemData(indexSelected).toString()+" like '"+arg1+"%' and r.datetime_output like '"+currentDate+"%'";
            else if(ui->tabWidget->currentIndex()==2)
                query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.comment,p.picture from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id where r.state like 'R%' and "+table+"."+ui->comboBox_filtered->itemData(indexSelected).toString()+" like '"+arg1+"%' and r.datetime_input like '"+currentDate+"%'";
            break;
        case 5: //patent_output, only for tab 2
            if(ui->tabWidget->currentIndex()==1) //(always 1 or not?)
                query = "select r.id,r.datetime_input,r.rut_people,p.names,p.paternal_surname,p.maternal_surname,c.name,pro.name,r.patent_input,r.patent_output,r.datetime_output,r.comment,p.picture from record as r left join people as p on r.rut_people=p.rut left join company as c on p.rut_company=c.rut left join profile as pro on p.id_profile=pro.id where r.state='C' and r."+ui->comboBox_filtered->itemData(indexSelected).toString()+" like '"+arg1+"%' and r.datetime_output like '"+currentDate+"%'";
            else
                QMessageBox::warning(this,tr("ALERTA"),tr("Primero seleccione tabla de salida."));
            break;
        }
    }
    clean("",true);
    loadTables(query);
}

void Dashboard::handlePeople(QString device){
    //    Devices:
    //    CS = ComboScan
    //    RT = RTScan

    QString imgPath;
    QString comment;

    QTime currentTime = QTime::currentTime();
    QDate currentDate = QDate::currentDate();

    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if (!qry->exec("select p.rut,p.names,p.paternal_surname,p.birthdate,co.name,p.state,na.code,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone,p.email,po.name,pro.name,p.picture,p.maternal_surname,fr.name from people as p left join company as co on p.rut_company=co.rut left join nationality as na on p.code_nationality=na.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as fr on p.id_frequency=fr.id where p.rut='"+global_PERSONAL_DATA+"'"))
    {

        qApp->beep();
        QMessageBox::critical(this,tr("ERROR"),error1);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
        statusBar()->showMessage(error1,5000);
    }
    else if (!qry->first()) //Person not found in db
    {
        if(device=="CS"){
            PERSONAL_DATA=global_PERSONAL_DATA; //rut.
            GIVENNAME=global_GIVENNAME;
            MATERNAL_SUR=global_MATERNAL_SURNAME;
            PATERNAL_SUR=global_PATERNAL_SURNAME;
            pr.CloseDevice();
            QMessageBox::critical(this,tr("PRECAUCION"),tr("Persona no se encuentra en la base de datos, se abrira el formulario de enrolamiento"));
            formcs Formcs(this);
            Formcs.exec();
        }else if(device=="RT"){
            pr.CloseDevice();
            QMessageBox::critical(this,tr("PRECAUCION"),tr("Persona no se encuentra en la base de datos, se abrira el formulario de enrolamiento"));
            formcs Formcs(this);
            Formcs.exec();

        }
    }
    else //Person found on db
    {
        QString query;
        //Compare personal data with database
        if(device=="CS"){
            if(global_GIVENNAME!=qry->value(NAMES).toString()){
                conn.updateDb(rutSignin,"update people set names = '"+global_GIVENNAME+"' where rut='"+global_PERSONAL_DATA+"'");
            }
            if(global_PATERNAL_SURNAME!=qry->value(PATERNAL_SURNAME).toString()){
                conn.updateDb(rutSignin,"update people set paternal_surname = '"+global_PATERNAL_SURNAME+"' where rut='"+global_PERSONAL_DATA+"'");
            }
            if(global_MATERNAL_SURNAME!=qry->value(MATERNAL_SURNAME).toString()){
                conn.updateDb(rutSignin,"update people set maternal_surname = '"+global_MATERNAL_SURNAME+"' where rut='"+global_PERSONAL_DATA+"'");
            }
            if(global_BIRTH_DATE!=qry->value(BIRTHDATE).toString()){
                conn.updateDb(rutSignin,"update people set birthdate = '"+global_BIRTH_DATE+"' where rut='"+global_PERSONAL_DATA+"'");
            }
        }
        else
        {
            global_GIVENNAME = qry->value(NAMES).toString();
            global_PATERNAL_SURNAME = qry->value(PATERNAL_SURNAME).toString();
            global_MATERNAL_SURNAME = qry->value(MATERNAL_SURNAME).toString();
        }

        //Get information from Db
        global_COMPANY=qry->value(COMPANY).toString();
        global_PROFILE=qry->value(PROFILE).toString();
        global_STATE=qry->value(STATE).toString();
        global_START_AUTHORIZED_HOUR=qry->value(START_AUTHORIZED_HOUR).toString();
        global_END_AUTHORIZED_HOUR=qry->value(END_AUTHORIZED_HOUR).toString();
        global_START_AUTHORIZED_DATE=qry->value(START_AUTHORIZED_DATE).toString();
        global_END_AUTHORIZED_DATE=qry->value(END_AUTHORIZED_DATE).toString();
        global_FREQUENCY=qry->value(FREQUENCY).toString();
        global_POSITION=qry->value(POSITION).toString();

        if(qry->value(PICTURE).toString().isNull()){
            global_PICTURE=":/images/User-blue-icon.png";
            if(device=="CS")
            {
                if(conn.getFirstFromDb(rutSignin, "select take_picture from configuration where key=(select key from users where rut = '"+rutSignin+"')") == "YES")
                {
                    int ret = QMessageBox::warning(this, tr("Advertencia"),
                                                   tr("Persona sin foto, si desea obtener, gire cedula al anverso y presione ok."),
                                                   QMessageBox::Ok | QMessageBox::Cancel);
                    if(ret==QMessageBox::Ok)
                    {
                        if(readAnverso(global_PERSONAL_DATA))
                        {
                            //imgPath = QDir::currentPath()+"/release/people/"+global_PERSONAL_DATA+".jpg";
                            imgPath = QDir::currentPath()+"/people/"+global_PERSONAL_DATA+".jpg";
                            conn.insert2Db(rutSignin,"update people set picture = '"+imgPath+"' where rut='"+global_PERSONAL_DATA+"'");
                            global_PICTURE = imgPath;
                        }
                    }
                }
            }
        }
        else
            global_PICTURE=qry->value(PICTURE).toString();

        ui->lineEdit_rut->setText(global_PERSONAL_DATA);
        ui->lineEdit_name->setText(global_GIVENNAME);
        ui->lineEdit_maternalSurname->setText(global_MATERNAL_SURNAME);
        ui->lineEdit_paternalSurname->setText(global_PATERNAL_SURNAME);
        ui->lineEdit_company->setText(global_COMPANY);
        ui->lineEdit_profile->setText(global_PROFILE);
        ui->lineEdit_position->setText(global_POSITION);

        QPixmap user(global_PICTURE);
        ui->label_user->setPixmap(user);

        //QFile pic(global_PICTURE); if(pic.exist())

        bool ok;
        QString recordState;
        QString authorizedBy;
        QDate startDate = QDate::fromString(global_START_AUTHORIZED_DATE,"yyyy-MM-dd");
        QDate endDate = QDate::fromString(global_END_AUTHORIZED_DATE,"yyyy-MM-dd");
        QTime startTime = QTime::fromString(global_START_AUTHORIZED_HOUR,"H:mm");
        QTime endTime = QTime::fromString(global_END_AUTHORIZED_HOUR,"H:mm");

        //Autorizher
        QStringList authorizer;
        QSqlQuery* qury=new QSqlQuery(conn.mydb);
        qury->prepare("select names,paternal_surname from users where id_rol=2");
        if(!qury->exec())
        {
            QMessageBox::critical(this,tr("ERROR"),error1);
            Logger::insert2Logger(rutSignin," ERROR ",error1);
        }
        else
            while(qury->next()){
                authorizer << qury->value(0).toString()+" "+qury->value(1).toString();
            }
        delete qury;

        //input or output?
        QString inputs=conn.getFirstFromDb(rutSignin,"select count(id) from record where state='O' and rut_people='"+global_PERSONAL_DATA+"'");
        bool flag_for_rejected; //true for output without question about contratista
        if(inputs.toInt() <= 0) // if exist some inputs
        {
            recordState = "O";
            ui->label_type->setText("ENTRADA");
            //no input with open state, it's input.
            if(global_STATE == "I") //People Inactive.
            {
                qApp->beep();
                do
                    authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Persona no activa.\n\n Solicite autorizacion e indique quien autoriza, en caso contrario presione boton cancelar."),authorizer,0,false,&ok);
                while(ok && authorizedBy.isEmpty());
                if (ok)
                {
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" no activa pero autorizada por "+authorizedBy);
                    authorizedBy = "[INACTIVO]: " + authorizedBy;
                    recordState = "O";
                }
                else
                {
                    recordState = "RIN"; //Rejected
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por no activa");
                    flag_for_rejected = true;
                }
                query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
            }
            else if(global_FREQUENCY == "PERMANENTE")
            {
                if(startDate.daysTo(currentDate) < 0)
                {
                    //Out of date range.
                    qApp->beep();

                    do
                        authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para esta fecha.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                    while(ok && authorizedBy.isEmpty());

                    if (ok)
                    {
                        authorizedBy = "[OUT OF DATE RANGE]: " + authorizedBy;
                        Logger::insert2Logger(rutSignin," DEBUG ", global_PERSONAL_DATA +" no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                        recordState = "O";
                    }
                    else
                    {
                        Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por intentar acceder fuera de rango de fecha");
                        recordState = "ROD";
                        flag_for_rejected = true;
                    }
                    query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
                }
                else
                {
                    if(!((startTime.secsTo(currentTime)>=0) && (currentTime.secsTo(endTime)>=0)))
                    {
                        //Out of time range.
                        qApp->beep();

                        do
                            authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                        while(ok && authorizedBy.isEmpty());
                        if (ok)
                        {
                            authorizedBy = "[OUT OF TIME RANGE]: " + authorizedBy;
                            Logger::insert2Logger(rutSignin," DEBUG ", global_PERSONAL_DATA +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                            recordState = "O";
                        }
                        else
                        {
                            Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por intentar acceder fuera de rango horario");
                            recordState="ROT";
                            flag_for_rejected = true;
                        }
                        query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
                    }
                }
            }
            else if(global_FREQUENCY != "PERMANENTE")
            {
                if(!((startDate.daysTo(currentDate)>=0) && (currentDate.daysTo(endDate)>=0)))
                {
                    //Out of date range.
                    qApp->beep();

                    do
                        authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para esta fecha.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                    while(ok && authorizedBy.isEmpty());

                    if (ok)
                    {
                        authorizedBy = "[OUT OF DATE RANGE]: " + authorizedBy;
                        Logger::insert2Logger(rutSignin," DEBUG ", global_PERSONAL_DATA +" no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                        recordState = "O";
                    }
                    else
                    {
                        Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por intentar acceder fuera de rango de fecha");
                        recordState = "ROD";
                        flag_for_rejected = true;
                    }
                    query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
                }
                else
                {
                    if(!((startTime.secsTo(currentTime)>=0) && (currentTime.secsTo(endTime)>=0)))
                    {
                        //Out of time range.
                        qApp->beep();

                        do
                            authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                        while(ok && authorizedBy.isEmpty());
                        if (ok)
                        {
                            authorizedBy = "[OUT OF TIME RANGE]: " + authorizedBy;
                            Logger::insert2Logger(rutSignin," DEBUG ", global_PERSONAL_DATA +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                            recordState = "O";
                        }
                        else
                        {
                            Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por intentar acceder fuera de rango horario");
                            recordState="ROT";
                            flag_for_rejected = true;
                        }
                        query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
                    }
                }
            }
            else if(!((startTime.secsTo(currentTime)>=0) && (currentTime.secsTo(endTime)>=0)))
            {
                //Out of time range.
                qApp->beep();

                do
                    authorizedBy = QInputDialog::getItem(this, tr("Ingreso Rechazado."),tr("Acceso no autorizado para este horario.\n\n Solicite autorizacion e indique quien autoriza:"),authorizer,0,false,&ok);
                while(ok && authorizedBy.isEmpty());
                if (ok)
                {
                    authorizedBy = "[OUT OF TIME RANGE]: " + authorizedBy;
                    Logger::insert2Logger(rutSignin," DEBUG ", global_PERSONAL_DATA +" accedió en horario no autorizado ("+currentDate.toString("yyyy-MM-dd")+currentTime.toString("HH:mm")+"), fué autorizado por "+authorizedBy);
                    recordState = "O";
                }
                else
                {
                    Logger::insert2Logger(rutSignin," DEBUG ", "Acceso de "+global_PERSONAL_DATA+" rechazada por intentar acceder fuera de rango horario");
                    recordState="ROT";
                    flag_for_rejected = true;
                }
                query="insert into record (datetime_input,rut_people,rut_user,type,state,authorized_by) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"','"+authorizedBy+"')";
            }
            if(query.isEmpty()){
                recordState = "O";
                query="insert into record (datetime_input,rut_people,rut_user,type,state) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','"+recordState+"')";
            }
        }
        //aca tengo que dejarlo
        else // Output
        {
            ui->label_type->setText("SALIDA");
            recordState = "C";
            //For 1 or more than 1 input withaout closed.
            //qry->prepare("select id from record where state='O' and rut_people='" + ui->lineEdit_rut->text()+"' and datetime_input not like'"+currentDate.toString("yyyy-MM-dd")+"%'");
            int input=0;
            if(!qry->exec("select id from record where state='O' and rut_people='" + ui->lineEdit_rut->text()+"'"))
            {
                QMessageBox::critical(this,tr("Error:"),error1);
                statusBar()->showMessage(error1,5000);
                Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
            }
            else
            {
                while(qry->next())
                    input++;
            }
            if(input > 1){
                QMessageBox::critical(this,tr("ADVERTENCIA"),tr("Persona mantiene registros sin cerrar, registre manualmente la salida primero."));
                query=""; //do nothing.
                ui->statusBar->clearMessage();

                ReadWithoutCI readWithoutCI(this);
                readWithoutCI.exec();
                on_actionActualizar_triggered();
            }
            else if(input == 1) //when have 1 input in state 'O' for any time. TIP: here also be defined 1 input for today.
            {
                QString dateTimeOutput = connection::getFirstFromDb(rutSignin,
                                                                    "select datetime_input from record where state='O' and rut_people='"+
                                                                    global_PERSONAL_DATA+"'");
                if(dateTimeOutput == (currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")))
                {
                    Logger::insert2Logger(rutSignin, " WARNING ","No se puede registrar la salida tan rápido, espere al menos 1 minuto.");
                    QMessageBox::warning(this,tr("WARNING"),tr("No se puede registrar la salida tan rápido, espere al menos 1 minuto."));
                    ui->statusBar->clearMessage();
                    query.clear();
                    clean("",true);
                    if(ui->tabWidget->currentIndex()==0)
                        loadTables("default_input");
                    else if(ui->tabWidget->currentIndex()==1)
                        loadTables("default_output");
                    else
                        loadTables("default_rejected");
                    loadLCD();
                }
                else
                {
                    QString id = conn.getFirstFromDb(rutSignin,
                                                     "select id from record where state='O' and rut_people='"+
                                                     global_PERSONAL_DATA+"'");
                    query="update record set state='"+recordState+"' ,datetime_output='"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+
                            "' where id='"+id+"'";
                }
            }
            else
                clean("",true); //can be removed this line.
        }
        if(!query.isEmpty()){
            conn.insert2Db(rutSignin,query);
            Logger::insert2Logger(rutSignin, " DEBUG ","Persona registrada existosamente.");
            ui->statusBar->showMessage("Persona registrada existosamente",3000); //3 secons to show message.

            clean("",true);
            if(ui->tabWidget->currentIndex()==0)
                loadTables("default_input");
            else if(ui->tabWidget->currentIndex()==1)
                loadTables("default_output");
            else
                loadTables("default_rejected");
            loadLCD();
        }
        else
            ui->statusBar->clearMessage();

    }
    pr.CloseDevice();
    delete qry;
}

void Dashboard::readFromPR()
{
    try
    {
        lib.FunctionStart("Connecting to the first device");
        pr.UseDevice(0,PR_UMODE_FULL_CONTROL);
        lib.FunctionEnd();

        if (!pr.IsValid())
        {
            lib.Error("Failed to initialize!");
        }
        else
        {
            if (!lib.KbHit())
            {
                lib.ProcessStart("Processing document");
                statusBar()->showMessage("Procesando cedula...");
                prDoc * doc = NULL;
                try
                {
                    std::vector<int> pages;
                    pages.push_back(pr.LightMask(PR_LIGHT_WHITE, PR_OW_DEFAULT));
                    if(!pages[0])
                        std::cout << "The device does not support the required lights!" << std::endl;
                    try {
                        pr.SetPageLight(pages);
                    } catch(gxException e) {
                        std::cerr << e.GetErrorStringA() << std::endl;
                    }

                    /* Capturing images */
                    lib.FunctionStart("Capturing images");
                    pr.Capture();
                    lib.FunctionEnd();

                    /* Getting document data */
                    lib.FunctionStart("Recognizing.");
                    doc = pr.Recognize(0);
                    lib.FunctionEnd();

                    if (!doc->IsValid())
                    {
                        qApp->beep();
                        statusBar()->showMessage("Carnet de identificacion ilegible.",5000);
                        Logger::insert2Logger(rutSignin, " ERROR ", "Carnet de identificacion no legible.");
                        QMessageBox::critical(this,tr("ERROR"),tr("Carnet de identificacion no legible."));
                        lib.WriteLine("No data found.");
                    }
                    else
                    {
                        string RUT;
                        bool Foreign=false; //for no chilean people

                        if(doc->FieldA(PR_DF_TYPE)=="ID")
                            RUT = doc->FieldA(PR_DF_DOCUMENT_NUMBER); // TYPE: ID, carnet viejo
                        else if(doc->FieldA(PR_DF_TYPE)=="IN")
                            RUT = doc->FieldA(PR_DF_PERSONAL_DATA); //TYPE: IN, carnet nuevo
                        else if(doc->FieldA(PR_DF_TYPE)=="P")
                            RUT = doc->FieldA(PR_DF_PERSONAL_DATA); // TYPE: P, passport
                        else{
                            RUT = doc->FieldA(PR_DF_DOCUMENT_NUMBER); //no chilean DNI, only pdf417.
                            Foreign=true;
                        }

                        if (RUT == "")
                        {
                            qApp->beep();
                            statusBar()->showMessage("Carnet de identificacion ilegible o al reverso.",5000);
                            Logger::insert2Logger(rutSignin, " ERROR ", "Carnet de identificacion no legible.");
                            QMessageBox::critical(this,tr("ERROR"),tr("Carnet de identificacion no legible o al reverso."));
                            lib.WriteLine("No data found.");
                        }
                        else
                        {
                            QSound::play("sounds/beep.wav");
                            global_PERSONAL_DATA = QString::fromStdString(RUT).replace(" ","");
                            qDebug()<<global_PERSONAL_DATA;
                            if(Foreign==true){
                                QStringList name = QString::fromStdString(doc->FieldA(PR_DF_NAME)).split(" ");
                                global_PATERNAL_SURNAME = name.at(0);
                                //                                global_MATERNAL_SURNAME = name.at(1);
                                global_GIVENNAME = name.at(1);
                            }
                            else
                            {
                                global_GIVENNAME = QString::fromStdString(doc->FieldA(PR_DF_GIVENNAME)).replace("<"," ");
                                QStringList surnames = QString::fromStdString(doc->FieldA(PR_DF_SURNAME)).split(" ");
                                global_PATERNAL_SURNAME = surnames.at(0);
                                global_MATERNAL_SURNAME = surnames.at(1);
                            }

                            global_CODE_NATIONALITY = QString::fromStdString(doc->FieldA(PR_DF_NATIONALITY));
                            global_BIRTH_DATE = QString::fromStdString(doc->FieldA(PR_DF_BIRTH_DATE));
                            if(global_BIRTH_DATE.mid(0,2).toInt() >= 0 && global_BIRTH_DATE.mid(0,2).toInt() <= 40)
                                global_BIRTH_DATE = "20"+global_BIRTH_DATE.mid(0,2)+"-"+global_BIRTH_DATE.mid(2,2)+"-"+global_BIRTH_DATE.mid(4,2);
                            else
                                global_BIRTH_DATE = "19"+global_BIRTH_DATE.mid(0,2)+"-"+global_BIRTH_DATE.mid(2,2)+"-"+global_BIRTH_DATE.mid(4,2);

                            handlePeople("CS");
                        }
                    }
                }
                catch (gxException e)
                {
                    lib.DisplExcp(e);
                }
                if (doc)
                    delete doc;
                lib.ProcessEnd();
            }
        }

    }
    catch (gxException e) {
        lib.DisplExcp(e);
        statusBar()->showMessage("ComboScan no conectado...",5);
        QPixmap badPix(":/images/bad.png");
        ui->label_status_cs->setPixmap(badPix);
    }
}

void Dashboard::bloodPanel(int segs){
    ui->lineEdit_rut->setStyleSheet("QLineEdit { border-color: rgb(0, 255, 0);}");
    ui->lineEdit_name->setStyleSheet("QLineEdit { border-color: rgb(0, 255, 0);}");
    ui->lineEdit_paternalSurname->setStyleSheet("QLineEdit { border-color: rgb(0, 255, 0);}");
    ui->lineEdit_maternalSurname->setStyleSheet("QLineEdit { border-color: rgb(0, 255, 0);}");
    ui->lineEdit_profile->setStyleSheet("QLineEdit { border-color: rgb(0, 255, 0);}");
}

bool Dashboard::readAnverso(QString rut)
{
    string text;
    string ec[]={"Ok","Warning","Error"};

    try
    {
        /* Connecting to the first device */
        lib.FunctionStart("Connecting to the first device");
        pr.UseDevice(0,PR_UMODE_FULL_CONTROL);
        lib.FunctionEnd();
        if (!pr.IsValid())
        {
            lib.Error("Failed to initialize!");
        }
        else
        {

            /* Using the device */
            if (!lib.KbHit()) {
                lib.ProcessStart("Processing document");
                prDoc * doc = NULL;

                lib.FunctionStart("Capturing images");
                pr.Capture();
                lib.FunctionEnd();

                lib.FunctionStart("Recognizing.");
                doc = pr.Recognize(0);
                lib.FunctionEnd();

                if (!doc->IsValid())
                {
                    lib.WriteLine("No data found.");
                }
                else
                {
                    /* Searching for the fields and displaying them */
                    gxVariant* pdoc = doc->ToVariant();
                    gxVariant fieldlist;
                    pdoc->GetChild(fieldlist, GX_VARIANT_BY_ID, PRV_FIELDLIST, 0);
                    int nitems = fieldlist.GetNItems();
                    for(int i = 0;i < nitems;i++)
                    {
                        gxVariant field;
                        fieldlist.GetItem(field, GX_VARIANT_BY_INDEX, 0, i);
                        int field_code = field.GetInt();
                        text = doc->FieldA(field_code);
                        if (text != "") lib.WriteLine("[" + lib.itos(field_code) + "] \"" + text + "\" [" + ec[doc->FieldStatus(field_code)/100] + "]");
                        if(field_code >= PR_DF_FORMATTED) continue;
                        try
                        {
                            gxImage* img = doc->FieldImage(field_code);
                            if(img->IsValid()){
                                if(field_code==2400){
                                    //QString imgPath = QDir::currentPath()+"/release/people/" + rut + ".jpg";
                                    QString imgPath = QDir::currentPath()+"/people/" + rut + ".jpg";
                                    img->Save(imgPath.toStdString(), GX_JPEG);
                                    return true;
                                }
                            }else{
                                QMessageBox::critical(this,tr("ERROR"),tr("No se pudo obtener la foto, verifique la posicion correcta del carnet y vuelva a intentar"));
                                return false;
                            }
                            if(img) delete img;
                        } catch (gxException e) {
                            lib.DisplExcp(e);
                            return false;
                        }
                    }
                    delete pdoc;
                }

                if (doc) delete doc;
                lib.ProcessEnd();
                //lib.WaitForSec(2);
            }

            /* Closing the device */
            lib.FunctionStart("Closing the device");
            pr.CloseDevice();
            lib.FunctionEnd();
        }
    }
    catch (gxException e)
    {
        lib.DisplExcp(e);
        return false;
    }
}

bool Dashboard::connectComboScan()
{
    try
    {
        if(!pr.IsValid())
        {
            lib.Error("Failed to initialize!");
            return false;
        }
        else
        {
            statusBar()->showMessage("Comboscan conectado exitosamente.",5000);
            return true;
        }
    }
    catch(gxException e) // e.GetErrorString()
    {
        QMessageBox::warning(this,tr("ERROR"),tr("Comboscan no conectado, conecte y detecte desde menu herramientas."));
        statusBar()->showMessage("ComboScan no conectado...",5000);
        Logger::insert2Logger(rutSignin," ERROR ", QString::number(e.GetErrorCode()));
        return false;
    }
}

void Dashboard::on_pushButton_clicked()
{
    readFromPR();
    if(comboScanIsOpen()==false){
        QMessageBox::warning(this,tr("PRECAUCION"),tr("Comboscan no conectado, conecte y detecte desde menu herramientas."));
    }
    ui->lineEdit_pdf417->setFocus();
}

void Dashboard::on_pushButton_rejected_clicked()
{
    if(ui->lineEdit_name->text().isEmpty())
        QMessageBox::critical(this,tr("ERROR"),tr("No hay persona registrada para rechazar."));
    else
    {
        QString comment;
        QMessageBox::StandardButton confirm;
        confirm = QMessageBox::question(this,tr("Confirmar"),
                                        tr("¿Está seguro que desea rechazar a: ")+ui->lineEdit_name->text()+
                                        " "+ui->lineEdit_paternalSurname->text()+" ?",QMessageBox::Yes|QMessageBox::No);
        if(confirm == QMessageBox::Yes){
            bool ok;
            do
                comment = QInputDialog::getText(this, tr("Ingreso Rechazado."),tr("Describa motivo para rechazar ingreso."),QLineEdit::Normal,"", &ok);
            while(ok && comment.isEmpty());
            if (ok)
            {

                connection::insert2Db(rutSignin,"update record set state = 'R', comment='"+comment+"' where datetime_input='"+global_DATETIME_INPUT+"' and rut_people='"+ui->lineEdit_rut->text()+"'");
                loadTables("default_input");
            }
        }
    }
}

void Dashboard::on_tableWidget_input_cellClicked(int row, int column)
{
    //Nothing right now.
}

void Dashboard::loadLCD(){
    int opened=0;
    int closed=0;
    int vehicles=0;
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    if(!qry->exec("select id from record where state='O' and datetime_input like '"+QDate::currentDate().toString("yyyy-MM-dd")+"%'"))
    {
        QMessageBox::critical(this,tr("Error:"),error1);
        statusBar()->showMessage(error1,5000);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
    }
    else
    {
        while(qry->next())
            opened++;
    }
    if(!qry->exec("select id from record where state='C' and datetime_output like '"+QDate::currentDate().toString("yyyy-MM-dd")+"%'"))
    {
        QMessageBox::critical(this,tr("Error:"),error1);
        statusBar()->showMessage(error1,5000);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
    }
    else
    {
        while(qry->next())
            closed++;
    }
    if(!qry->exec("select id from record where state ='O' and patent_input != '' and datetime_input like '"+QDate::currentDate().toString("yyyy-MM-dd")+"%'"))
    {
        QMessageBox::critical(this,tr("Error:"), qry->lastError().text()+" "+qry->executedQuery());
        statusBar()->showMessage(error1,5000);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
    }
    else
    {
        while(qry->next())
            vehicles++;
    }
    ui->lcd_opened->display(opened);
    ui->lcd_vehicles->display(vehicles);
    ui->lcdNumber->display(closed);
    delete qry;
}

void Dashboard::on_tableWidget_input_cellChanged(int row, int column)
{
    QTableWidgetItem* cellChanged = ui->tableWidget_input->item(row, column);
    QTableWidgetItem* idItem = ui->tableWidget_input->item(row, 0);
    if(column == 8){
        QString patentCurrent = connection::getFirstFromDb(rutSignin,"select patent_input from record where id = "+idItem->text());
        if(cellChanged->text() != patentCurrent){
            connection::insert2Db(rutSignin,"update record set patent_input = '"+cellChanged->text()+"' where id = "+idItem->text());
            loadLCD();
        }
    }else if(column == 9){
        QString commentCurrent = connection::getFirstFromDb(rutSignin,"select comment from record where id = "+idItem->text());
        if(cellChanged->text() != commentCurrent)
            connection::insert2Db(rutSignin,"update record set comment = '"+cellChanged->text()+"' where id = "+idItem->text());
    }
}

void Dashboard::on_actionDetectar_ComboScan_triggered()
{
    if(comboScanIsOpen()==true)
    {
        QPixmap okPix(":/images/ok.png");
        ui->label_status_cs->setPixmap(okPix);
        Logger::insert2Logger(rutSignin," DEBUG ", "ComboScan conectado.");
    }
    else
    {
        QPixmap badPix(":/images/bad.png");
        ui->label_status_cs->setPixmap(badPix);
    }
}

void Dashboard::on_actionRegistro_Manual_triggered()
{
    ReadWithoutCI readwithoutci(this);
    readwithoutci.exec();
    on_actionActualizar_triggered();
}

void Dashboard::exit(){
    close();
    qApp->quit();
}

void Dashboard::on_actionSalir_triggered()
{
    // delete ui;
    // Dashboard::exit();
    qApp->exit();
}

void Dashboard::on_actionExportar_triggered()
{
    ExportRecords exportRecords(this);
    exportRecords.exec();
}

void Dashboard::clean(QString type, bool personalPanel)
{
    int i;
    ui->label_type->setText("");
    if(type=="O")
    {
        for(i = ui->tableWidget_input->rowCount();i>=0;i--)
            ui->tableWidget_input->removeRow(i);
    }
    else if(type=="C")
    {
        for(i = ui->tableWidget_output->rowCount();i>=0;i--)
            ui->tableWidget_output->removeRow(i);
    }
    else if(type=="R")
    {
        for(i = ui->tableWidget_rejected->rowCount();i>=0;i--)
            ui->tableWidget_rejected->removeRow(i);
    }
    else if(type=="RT"){
        global_PERSONAL_DATA="";
        global_GIVENNAME="";
        global_PATERNAL_SURNAME="";
        global_MATERNAL_SURNAME="";
    }
    else
    {
        global_PERSONAL_DATA=""; //rut.
        global_GIVENNAME="";
        global_MATERNAL_SURNAME="";
        global_PATERNAL_SURNAME="";
        global_BIRTH_DATE="";
        global_CODE_NATIONALITY="";
        global_NATIONALITY="";
        global_DOCUMENT_NUMBER="";
        global_TYPE="";
        global_COMPANY="";
        global_PROFILE="";
        global_STATE="";
        global_START_AUTHORIZED_HOUR="";
        global_END_AUTHORIZED_HOUR="";
        global_START_AUTHORIZED_DATE="";
        global_END_AUTHORIZED_DATE="";
        global_PICTURE="";
        global_DATETIME_INPUT=""; //used for rejecting access.
    }

    if(personalPanel)
    {
        ui->lineEdit_rut->setText("");
        ui->lineEdit_name->setText("");
        ui->lineEdit_paternalSurname->setText("");
        ui->lineEdit_maternalSurname->setText("");
        ui->lineEdit_profile->setText("");
        ui->lineEdit_company->setText("");
        ui->lineEdit_position->setText("");
        QPixmap user(":images/User-blue-icon.png");
        ui->label_user->setPixmap(user);
    }
}

void Dashboard::on_tabWidget_currentChanged(int index)
{
    QString query;
    switch(index)
    {
    case 0:
        query = "default_input";
        ui->pushButton_rejected->setEnabled(true);
        break ;
    case 1 :
        query = "default_output";
        ui->pushButton_rejected->setEnabled(false);
        break ;
    case 2 :
        query = "default_rejected";
        ui->pushButton_rejected->setEnabled(false);
        break ;
    }
    clean("O",true);
    clean("C",true);
    clean("R",true);
    loadTables(query);
}

void Dashboard::on_actionHistorial_triggered()
{
    Logger logger(this);
    logger.exec();
}

void Dashboard::on_tableWidget_output_cellChanged(int row, int column)
{
    QTableWidgetItem* cellChanged = ui->tableWidget_output->item(row, column);
    QTableWidgetItem* idItem = ui->tableWidget_output->item(row, 0);
    if(column == 9){
        QString patentCurrent = connection::getFirstFromDb(rutSignin,"select patent_output from record where id = "+idItem->text());
        if(cellChanged->text() != patentCurrent){
            connection::insert2Db(rutSignin,"update record set patent_output = '"+cellChanged->text()+"' where id = "+idItem->text());
            loadLCD();
        }
    }else if(column == 11){
        QString commentCurrent = connection::getFirstFromDb(rutSignin,"select comment from record where id = "+idItem->text());
        if(cellChanged->text() != commentCurrent)
            connection::insert2Db(rutSignin,"update record set comment = '"+cellChanged->text()+"' where id = "+idItem->text());
    }
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_actionCerrar_Sesi_n_triggered()
{
    //this->close();
    Logger::insert2Logger(rutSignin," INFO ","Sesion closed.");
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void Dashboard::showTime()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    QString datetimetext = dateTime.toString("yyyy-MM-dd");
    ui->label_currentDate->setText(datetimetext);
    ui->label_currentDate->setStyleSheet("color: rgb(228, 115, 75);");
    //on_actionActualizar_triggered();

}

void Dashboard::on_actionImportarPersonas_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Seleccione archivo"), "", tr("xlsx Files (*.xlsx)"));
    QXlsx::Document xlsx(file);
    connection conn;

    int exist=0;
    int newPeople=0;

    QString rut;
    QString givenname;
    QString paternal_surname;
    QString maternal_surname;
    QDate birthdate;
    QString company;
    QString state;
    QString nationality;
    QString cellphone;
    QString email;
    QString position;
    QString profile;
    QString frequency;
    QDate start_authorized_date;
    QDate end_authorized_date;
    QTime start_authorized_hour;
    QTime end_authorized_hour;

    QString query;

    QProgressDialog progress("Importando personas...", "Abortar", 2, xlsx.dimension().lastRow(), this);
    progress.setWindowModality(Qt::WindowModal);

    for (int row=2; row <= xlsx.dimension().lastRow(); row++)
    {
        progress.setValue(row);
        rut = xlsx.read("A"+QString::number(row)).toString();
        rut.remove("-");
        rut.toUpper(); // for k;
        if(rut.isEmpty()){break;}
        if(!conn.getFirstFromDb(rutSignin,"select rut from people where rut='"+rut+"'").isEmpty())
            exist++;
        else
        {
            if(!xlsx.read("B"+QString::number(row)).isNull())
            {
                givenname = xlsx.read("B"+QString::number(row)).toString();
                givenname.trimmed();
                if(!xlsx.read("C"+QString::number(row)).isNull())
                {
                    paternal_surname = xlsx.read("C"+QString::number(row)).toString();
                    paternal_surname.trimmed();
                    if(!xlsx.read("D"+QString::number(row)).isNull())
                    {
                        maternal_surname = xlsx.read("D"+QString::number(row)).toString();
                        maternal_surname.trimmed();
                        if(!xlsx.read("F"+QString::number(row)).isNull())
                        {
                            company = xlsx.read("F"+QString::number(row)).toString();
                            company.trimmed();
                            if(!xlsx.read("G"+QString::number(row)).isNull())
                            {
                                state = xlsx.read("G"+QString::number(row)).toString();
                                state.trimmed();
                                if(!xlsx.read("H"+QString::number(row)).isNull())
                                {
                                    nationality = xlsx.read("H"+QString::number(row)).toString();
                                    nationality.trimmed();
                                    if(!xlsx.read("K"+QString::number(row)).isNull())
                                    {
                                        position = xlsx.read("K"+QString::number(row)).toString();
                                        position.trimmed();
                                        if(!xlsx.read("L"+QString::number(row)).isNull())
                                        {
                                            profile = xlsx.read("L"+QString::number(row)).toString();
                                            profile.trimmed();
                                            if(!xlsx.read("M"+QString::number(row)).isNull())
                                            {
                                                frequency = xlsx.read("M"+QString::number(row)).toString();
                                                frequency.trimmed();
                                                if(!xlsx.read("N"+QString::number(row)).isNull())
                                                {
                                                    start_authorized_date = QDate::fromString(xlsx.read("N"+QString::number(row)).toString(),"yyyy-MM-dd"); // for some reason no set format.
                                                    if(frequency != "Permanente")
                                                    {
                                                        if(!xlsx.read("O"+QString::number(row)).isNull())
                                                            end_authorized_date = QDate::fromString(xlsx.read("O"+QString::number(row)).toString(),"yyyy-MM-dd"); // for some reason no set format.
                                                        else
                                                        {
                                                            QMessageBox::critical(this,tr("ERROR"),tr("Campo fin de fecha de autorizacion no puede estar vacía."));
                                                            break;
                                                        }
                                                    }
                                                    else
                                                        end_authorized_date = QDate::fromString(xlsx.read("O"+QString::number(row)).toString(),"yyyy-MM-dd"); // for some reason no set format.
                                                    if(!xlsx.read("P"+QString::number(row)).isNull())
                                                    {
                                                        start_authorized_hour = QTime::fromString(xlsx.read("P"+QString::number(row)).toString(),"HH:mm:ss");
                                                        if(!xlsx.read("Q"+QString::number(row)).isNull())
                                                            end_authorized_hour = QTime::fromString(xlsx.read("Q"+QString::number(row)).toString(),"HH:mm:ss");
                                                        else{
                                                            QMessageBox::critical(this,tr("ERROR"),tr("Campo fin horario de autorizacion no puede estar vacío."));
                                                            break;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        QMessageBox::critical(this,tr("ERROR"),tr("Campo inicio horario de autorizacion no puede estar vacío."));
                                                        break;
                                                    }
                                                }
                                                else
                                                {
                                                    QMessageBox::critical(this,tr("ERROR"),tr("Campo inicio de fecha de autorizacion no puede estar vacía."));
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                QMessageBox::critical(this,tr("ERROR"),tr("Campo frecuencia no puede estar vacía."));
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            QMessageBox::critical(this,tr("ERROR"),tr("Campo perfil no puede estar vacío."));
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        QMessageBox::critical(this,tr("ERROR"),tr("Campo posición no puede estar vacío."));
                                        break;
                                    }
                                }
                                else
                                {
                                    QMessageBox::critical(this,tr("ERROR"),tr("Campo nacionalidad no puede estar vacío."));
                                    break;
                                }
                            }
                            else
                            {
                                QMessageBox::critical(this,tr("ERROR"),tr("Campo estado no puede estar vacío."));
                                break;
                            }
                        }
                        else
                        {
                            QMessageBox::critical(this,tr("ERROR"),tr("Campo empresa no puede estar vacío."));
                            break;
                        }
                    }
                    //                    else
                    //                    {
                    //                        QMessageBox::critical(this,tr("ERROR"),tr("Campo apellido materno no puede estar vacío."));
                    //                        break;
                    //                    }
                }
                else
                {
                    QMessageBox::critical(this,tr("ERROR"),tr("Campo apellido paterno no puede estar vacío."));
                    break;
                }
            }
            else
            {
                QMessageBox::critical(this,tr("ERROR"),tr("Campo nombre no puede estar vacío."));
                break;
            }

            if(xlsx.read("E"+QString::number(row)).isNull())
                birthdate = QDate::fromString("1900-01-01","yyyy-MM-dd");
            else
                birthdate = QDate::fromString(xlsx.read("E"+QString::number(row)).toString(),"yyyy-MM-dd"); // for some reason no set format.

            if(xlsx.read("I"+QString::number(row)).isNull())
                cellphone = "0";
            else
                cellphone = xlsx.read("I"+QString::number(row)).toString();

            if(xlsx.read("J"+QString::number(row)).isNull())
                email = "";
            else
                email = xlsx.read("J"+QString::number(row)).toString();

            //insert to db
            if(state=="ACTIVO")
                state = "A";
            else if(state == "INACTIVO")
                state = "I";

            company = conn.getFirstFromDb(rutSignin,"select rut from company where name = '"+company.simplified()+"'");
            if(company.isEmpty())
            {
                QMessageBox::critical(this,tr("ERROR"), "La empresa de "+givenname+" "+paternal_surname+" "+maternal_surname+" rut: "+rut+" no se encuentra en la base de datos, favor verificar el archivo excel y volver a intentar.");
                break;
            }
            nationality = conn.getFirstFromDb(rutSignin,"select code from nationality where name like '"+nationality+"'");
            if(nationality.isEmpty())
            {
                QMessageBox::critical(this,tr("ERROR"), "La nacionalidad de "+givenname+" "+paternal_surname+" "+maternal_surname+" rut: "+rut+" no se encuentra en la base de datos, favor verificar el archivo excel y volver a intentar.");
                break;
            }
            position = conn.getFirstFromDb(rutSignin,"select id from position where name like '"+position.simplified()+"'");
            if(position.isEmpty())
            {
                QMessageBox::critical(this,tr("ERROR"), "El cargo de "+givenname+" "+paternal_surname+" "+maternal_surname+" rut: "+rut+" no se encuentra en la base de datos, favor verificar el archivo excel y volver a intentar.");
                break;
            }
            profile = conn.getFirstFromDb(rutSignin,"select id from profile where name like '"+profile.simplified()+"'");
            if(profile.isEmpty())
            {
                QMessageBox::critical(this,tr("ERROR"), "El perfíl de "+givenname+" "+paternal_surname+" "+maternal_surname+" rut: "+rut+" no se encuentra en la base de datos, favor verificar el archivo excel y volver a intentar.");
                break;
            }
            frequency = conn.getFirstFromDb(rutSignin,"select id from frequency where name like '"+frequency+"'");
            if(frequency.isEmpty())
            {
                QMessageBox::critical(this,tr("ERROR"), "La frecuencia de acceso de "+givenname+" "+paternal_surname+" "+maternal_surname+" rut: "+rut+" no se encuentra en la base de datos, favor verificar el archivo excel y volver a intentar.");
                break;
            }
            if(position.isEmpty())
                position = "0";
            if(profile.isEmpty())
                profile = "0";
            if(frequency.isEmpty())
                frequency = "0";

            query = "insert into people (rut,names,paternal_surname,maternal_surname,birthdate,rut_company,state,code_nationality,cellphone,email,id_position,id_profile,id_frequency,start_authorized_date,end_authorized_date,start_authorized_hour,end_authorized_hour) values ('"+
                    rut+"','"+givenname.toUpper()+"','"+paternal_surname.toUpper()+"','"+maternal_surname.toUpper()+"','"+birthdate.toString("yyyy-MM-dd")+"','"+
                    company.toUpper()+"','"+state+"','"+nationality.toUpper()+"',"+cellphone+",'"+email.toUpper()+"',"+position.toUpper()+","+
                    profile.toUpper()+","+frequency.toUpper()+",'"+start_authorized_date.toString("yyyy-MM-dd")+"','"+
                    end_authorized_date.toString("yyyy-MM-dd")+"','"+
                    start_authorized_hour.toString("h:mm")+"','"+
                    end_authorized_hour.toString("h:mm")+"')";

            conn.insert2Db(rutSignin,query);
            newPeople++;
            Logger::insert2Logger(rutSignin," DEBUG ",query);
        }
    }
    progress.setValue(xlsx.dimension().lastRow());
    QString msg = QString::number(newPeople) + " de "+QString::number(xlsx.dimension().lastRow())+" personas importadas\n"+ QString::number(exist) + " personas ya existian.";
    QMessageBox::information(this,tr("INFORMACIÓN"),msg);
}

void Dashboard::on_actionAdministrarPersonas_triggered()
{
    People people(this);
    people.exec();
}

void Dashboard::on_actionAdministrarUsuarios_triggered()
{
    Users users(this);
    users.exec();
}

void Dashboard::on_actionImportarEmpresas_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Seleccione archivo"), "", tr("xlsx Files (*.xlsx)"));
    QXlsx::Document xlsx(file);
    connection conn;

    int exist=0;
    int newCompany=0;

    QString rut;
    QString name;
    QString query;

    for (int row=2; row <= xlsx.dimension().lastRow(); row++)
    {
        if(xlsx.read("A"+QString::number(row)).toString().isEmpty()){break;}
        if(!conn.getFirstFromDb(rutSignin,"select rut from company where rut='"+xlsx.read("A"+QString::number(row)).toString()+"'").isEmpty())
            exist++;
        else
        {
            newCompany++;
            rut = xlsx.read("A"+QString::number(row)).toString();
            if(!xlsx.read("B"+QString::number(row)).isNull())
            {
                name = xlsx.read("B"+QString::number(row)).toString();
                name.trimmed();
                name.toUpper();
                name.simplified();
            }
            else
            {
                QMessageBox::critical(this,tr("ERROR"),tr("Campo nombre no puede estar vacío."));
                break;
            }

            query = "insert into company (rut,name) values ('"+rut+"','"+name+"')";
            conn.insert2Db(rutSignin,query);
            Logger::insert2Logger(rutSignin," DEBUG ",query);
        }
    }
    QString msg = QString::number(newCompany) + " empresas importadas\n"+ QString::number(exist)+ " empresas ya existian.";
    QMessageBox::information(this,tr("INFORMACIÓN"),msg);
}

void Dashboard::on_actionImportarCargos_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Seleccione archivo"), "", tr("xlsx Files (*.xlsx)"));
    QXlsx::Document xlsx(file);
    connection conn;

    int exist=0;
    int newPosition=0;

    QString name;
    QString query;

    for (int row=2; row <= xlsx.dimension().lastRow(); row++)
    {
        if(xlsx.read("A"+QString::number(row)).toString().isEmpty()){break;}
        if(!conn.getFirstFromDb(rutSignin,"select id from position where name='"+xlsx.read("A"+QString::number(row)).toString()+"'").isEmpty())
            exist++;
        else
        {
            newPosition++;
            name = xlsx.read("A"+QString::number(row)).toString();
            name.trimmed();
            name.toUpper();
            name.simplified();

            query = "insert into position (name) values ('"+name+"')";
            conn.insert2Db(rutSignin,query);
            Logger::insert2Logger(rutSignin," DEBUG ",query);
        }
    }
    QString msg = QString::number(newPosition) + " cargos importados\n"+ QString::number(exist)+ " cargos ya existian.";
    QMessageBox::information(this,tr("INFORMACIÓN"),msg);
}

void Dashboard::on_actionImportarPerfiles_triggered()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Seleccione archivo"), "", tr("xlsx Files (*.xlsx)"));
    QXlsx::Document xlsx(file);
    connection conn;

    int exist=0;
    int newProfile=0;

    QString name;
    QString query;

    for (int row=2; row <= xlsx.dimension().lastRow(); row++)
    {
        if(xlsx.read("A"+QString::number(row)).toString().isEmpty()){break;}
        if(!conn.getFirstFromDb(rutSignin,"select id from profile where name='"+xlsx.read("A"+QString::number(row)).toString()+"'").isEmpty())
            exist++;
        else
        {
            newProfile++;
            name = xlsx.read("A"+QString::number(row)).toString();
            name.trimmed();
            name.toUpper();
            name.simplified();

            query = "insert into profile (name) values ('"+name+"')";
            conn.insert2Db(rutSignin,query);
            Logger::insert2Logger(rutSignin," DEBUG ",query);
        }
    }
    QString msg = QString::number(newProfile) + " perfiles importados\n"+ QString::number(exist)+ " perfiles ya existian.";
    QMessageBox::information(this,tr("INFORMACIÓN"),msg);
}

void Dashboard::on_actionAdministrarEmpresas_triggered()
{
    Companies companies(this);
    companies.exec();
}

void Dashboard::on_actionActualizar_triggered()
{
    if(ui->tabWidget->currentIndex()==0)
        loadTables("default_input");
    else if(ui->tabWidget->currentIndex()==1)
        loadTables("default_output");
    else if(ui->tabWidget->currentIndex()==2)
        loadTables("default_rejected");
}

void Dashboard::on_lineEdit_pdf417_editingFinished()
{

}

void Dashboard::on_lineEdit_pdf417_selectionChanged()
{
    ui->lineEdit_pdf417->setFocus();
}

void Dashboard::on_pushButton_userProfile_clicked()
{
    UserProfile userprofile(this);
    userprofile.exec();
    connection conn;
    ui->label_userName->setText(conn.getFirstFromDb(rutSignin,"select names from users where rut='"+rutSignin+"'"));
}

void Dashboard::on_actionIndividual_triggered()
{
    IndividualReport individualreport(this);
    individualreport.exec();
}

void Dashboard::on_actionRechazados_triggered()
{
    RejectedReport rejectedreport(this);
    rejectedreport.exec();
}

void Dashboard::on_actionConfiguraci_n_triggered()
{
    Configuration conf(this);
    conf.exec();
}

bool Dashboard::RtIsConnected()
{

}

void Dashboard::on_actionDiario_triggered()
{
    DailyReport dr(this);
    dr.exec();
}

void Dashboard::serialReceived(){

    serialBuffer = "";
    serialData = "";
    serialData = RTScan->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    QStringList bufferSplit = serialBuffer.split(" ");
    QString rut = bufferSplit[0].toUtf8();
    serialData="";
    bufferSplit.clear();
    serialBuffer="";
    qDebug()<<"raw: "+rut;

    if(rut.startsWith("https"))
    {
        //52 hasta 60 contiene el rut.
        rut = rut.mid(52,8); // 8 digitos a partir del 52.
        if(rut.endsWith("-"))
            rut.remove("-");
    }
    else if(rut.at(0).isDigit()){
        rut.resize(8);
    }
    qDebug()<<"Rut: " + rut;
    if(rut.at(0).isDigit()){
        connection conn;
        global_PERSONAL_DATA = conn.getFirstFromDb(rutSignin,"select rut from people where rut like '"+rut+"%'");
        if(global_PERSONAL_DATA.isEmpty())
            ui->lineEdit_pdf417->setText(rut);
        else
            ui->lineEdit_pdf417->setText(global_PERSONAL_DATA);
    }
}

void Dashboard::on_lineEdit_pdf417_textChanged(const QString &arg1)
{
    if(!ui->lineEdit_pdf417->text().isEmpty()){
        global_PERSONAL_DATA=arg1; // for paste directly in this textbox.
        handlePeople("RT");
        ui->lineEdit_pdf417->setText("");
    }
}

void Dashboard::on_actionDetectar_RTScan_triggered()
{
    if(RTScan->isOpen()){
        //qDebug()<<RTScan->portName();
        connection conn;
        //        foreach (const QSerialPortInfo &Ports, QSerialPortInfo::availablePorts())
        //            ui->comboBox_rtscan->addItem(Ports.portName());

        if(RTScan->portName() == conn.getFirstFromDb(rutSignin,"select rtscan_port from configuration where key=(select key from users where rut = '"+rutSignin+"')"))
        {
            /*comparar con portname que aparece en el foreach*/
            QPixmap okPix(":/images/ok.png");
            ui->label_status_lect->setPixmap(okPix);
        }
        else
        {
            QMessageBox::warning(this,tr("WARNING"),tr("Debe actualizar el puerto del dispositivo."));
            Configuration c(this);
            c.exec();
        }
    }else{
        QPixmap badPix(":/images/bad.png");
        ui->label_status_lect->setPixmap(badPix);
        Logger::insert2Logger(rutSignin," ERROR ", "ComboScan desconectado.");
    }
}

void Dashboard::on_actionGeneral_triggered()
{
    ExportRecords er(this);
    er.exec();
}

void Dashboard::on_pushButton_updatePic_clicked()
{
    if(!ui->lineEdit_rut->text().isEmpty())
    {
        //QFile pic (QDir::currentPath()+"/release/people/"+ui->lineEdit_rut->text()+".jpg");
        QFile pic(QDir::currentPath()+"/people/"+ui->lineEdit_rut->text()+".jpg");
        if(pic.exists())
            pic.remove();
        if(readAnverso(ui->lineEdit_rut->text()))
        {
            connection conn;
            conn.updateDb(rutSignin,"update people set picture='"+pic.fileName()+"' where rut='"+ui->lineEdit_rut->text()+"'");
            QPixmap user(pic.fileName());
            user.load(pic.fileName());
            ui->label_user->setPixmap(user);
        }
        if(!pic.exists())
            QMessageBox::information(this,tr("INFORMACION"),"Persona sin foto, porfavor verifique la posicion del carnet");
    }
}

void Dashboard::on_actionEnrolar_triggered()
{
    PERSONAL_DATA="";
    GIVENNAME="";
    MATERNAL_SUR="";
    PATERNAL_SUR="";

    if(comboScanIsOpen()==true)
    {
        pr.CloseDevice();
        formcs Formcs(this);
        Formcs.exec();
        on_actionActualizar_triggered();
    }else if(comboScanIsOpen()==false){
        QMessageBox::warning(this,tr("ERROR"),tr("Dispositivo Enrolador(COMBOSCAN), no se encuentra conectado, Verifique"));

    }
}
/*void Dashboard::quitAplication()
{
 QCoreApplication::quit();
}*/
void Dashboard::on_actionAdministrar_2_triggered()
{
    disconnect(RTScan, SIGNAL(readyRead()),this,SLOT(serialReceived()));
    administratorMenu admin(this);
    admin.exec();
    connect(RTScan, SIGNAL(readyRead()),this,SLOT(serialReceived()));
}
