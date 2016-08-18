#include "formcs.h"
#include "ui_formcs.h"

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
#include <QDebug>
#include <QCompleter>
#include <dashboard.h>

#include <connection.h>
#include <QtCore>

//Necesary for PR
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "include/prapi.h"
#include "include/gxsd.h"
//#include "include/gxsdldr.cpp"
#include "__lib__.h"

#include <QProgressDialog>
#include <QtWidgets/QApplication>

PassportReader pr1;  /* Object for the PR system */
QSerialPort *RTScan1; /* Object for the RTscan */
QTime currentTime = QTime::currentTime();
QDate currentDate = QDate::currentDate();
connection conn1;
Lib lib1;

QString global_PERSONAL_DATA1; //rut.
QString global_GIVENNAME1;
QString global_MATERNAL_SURNAME1;
QString global_PATERNAL_SURNAME1;
QString global_BIRTH_DATE1;
QString global_CODE_NATIONALITY1;
QString global_NATIONALITY1;
QString global_DOCUMENT_NUMBER1;
QString global_TYPE1;
QString global_COMPANY1;
QString global_PROFILE1;
QString global_POSITION1;
QString global_STATE1;
QString global_START_AUTHORIZED_HOUR1;
QString global_END_AUTHORIZED_HOUR1;
QString global_START_AUTHORIZED_DATE1;
QString global_END_AUTHORIZED_DATE1;
QString global_PICTURE1;
QString global_DATETIME_INPUT1; //used for rejecting access.
QString global_FREQUENCY1;
QString imgPath;
QString from;
#ifdef GX_NAMESPACES
using namespace gx; //jdk
using namespace pr; //API
#endif
using namespace std;
formcs::formcs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formcs)
{
    QPixmap blueIconUser(":images/User-blue-icon.png");
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Formulario Enrolamiento");
    ui->formcs_labelImage->setPixmap(blueIconUser);
    ui->lineEdit_rut->setEnabled(false);
    ui->lineEdit_name->setEnabled(false);
    ui->lineEdit_Enterprise->setEnabled(false);
    ui->lineEdit_appMat->setEnabled(false);
    ui->lineEdit_appPat->setEnabled(false);
    ui->lineEdit_position->setEnabled(false);
    ui->comboBox_profile->setEnabled(false);

    /*  switch (conn2.getFirstFromDb(rutSignin,"select id_rol from users where rut='"+rutSignin+"'").toInt()) {
    case 2: //Authorizer
        ui->button_manualRegistration->setEnabled(false);
        break;
    case 3: //Administrator
        ui->button_manualRegistration->setEnabled(true);
        break;
    case 1: //Operator
        ui->button_manualRegistration->setEnabled(false);
        break;
    case 4: //Supervisor
        ui->button_manualRegistration->setEnabled(true);
        break;
    default:
        break;
    }*/
    if(!PERSONAL_DATA.isEmpty()){
        ui->lineEdit_rut->setText(PERSONAL_DATA);
        ui->lineEdit_name->setText(GIVENNAME);
        ui->lineEdit_appMat->setText(MATERNAL_SUR);
        ui->lineEdit_appPat->setText(PATERNAL_SUR);
        ui->lineEdit_position->setEnabled(true);
        ui->comboBox_profile->setEnabled(true);
        ui->lineEdit_Enterprise->setEnabled(true);
        ui->button_manualRegistration->setEnabled(false);
        ui->pushButton_2->setEnabled(false);


    }

    //focus in the button "obtener informacion"
    ui->pushButton_2->setFocus();

    //Set the information in the combobox profile
    QSqlQuery* qry=new QSqlQuery(conn1.mydb);
    QSqlQueryModel * profileModal=new QSqlQueryModel();
    qry->exec("select name from profile order by name asc");
    profileModal->setQuery(*qry);
    ui->comboBox_profile->setModel(profileModal);
    ui->comboBox_profile->setCurrentIndex(-1);
    
}

formcs::~formcs()
{
    delete ui;
}


void formcs::on_CancelButton_formcs_clicked()
{
	clean();
    pr1.CloseDevice();
    formcs::close();
}
void formcs::readFromFirstDevice()
{

    try
    {
        lib1.FunctionStart("Connecting to the first device");
        pr1.UseDevice(0,PR_UMODE_FULL_CONTROL);
        lib1.FunctionEnd();

        if (!pr1.IsValid())
        {
            lib1.Error("Failed to initialize!");
        }
        else
        {
            if (!lib1.KbHit())
            {
                lib1.ProcessStart("Processing document");
                // statusBar()->showMessage("Procesando cedula...");
                prDoc * doc = NULL;
                try
                {
                    std::vector<int> pages;
                    pages.push_back(pr1.LightMask(PR_LIGHT_WHITE, PR_OW_DEFAULT));
                    if(!pages[0])
                        std::cout << "The device does not support the required lights!" << std::endl;
                    try {
                        pr1.SetPageLight(pages);
                    } catch(gxException e) {
                        std::cerr << e.GetErrorStringA() << std::endl;
                    }

                    // Capturing images
                    lib1.FunctionStart("Capturing images");
                    pr1.Capture();
                    lib1.FunctionEnd();

                    //Getting document data
                    lib1.FunctionStart("Recognizing.");
                    doc = pr1.Recognize(0);
                    lib1.FunctionEnd();

                    if (!doc->IsValid())
                    {
                        qApp->beep();
                        //     statusBar()->showMessage("Carnet de identificacion ilegible.",5000);
                        Logger::insert2Logger(rutSignin, " ERROR ", "Carnet de identificacion no legible.");
                        QMessageBox::critical(this,tr("ERROR"),tr("Carnet de identificacion no legible."));
                        lib1.WriteLine("No data found.");
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
                            //        statusBar()->showMessage("Carnet de identificacion ilegible o al reverso.",5000);
                            Logger::insert2Logger(rutSignin, " ERROR ", "Carnet de identificacion no legible.");
                            QMessageBox::critical(this,tr("ERROR"),tr("Carnet de identificacion no legible o al reverso."));
                            lib1.WriteLine("No data found.");
                        }
                        else
                        {
                            QSound::play("sounds/beep.wav");
                            global_PERSONAL_DATA1 = QString::fromStdString(RUT).replace(" ","");
                            qDebug()<<global_PERSONAL_DATA1;
                            if(Foreign==true){
                                QStringList name = QString::fromStdString(doc->FieldA(PR_DF_NAME)).split(" ");
                                global_PATERNAL_SURNAME1 = name.at(0);
                                //                                global_MATERNAL_SURNAME = name.at(1);
                                global_GIVENNAME1 = name.at(1);
                            }
                            else
                            {
                                global_GIVENNAME1 = QString::fromStdString(doc->FieldA(PR_DF_GIVENNAME)).replace("<"," ");
                                QStringList surnames = QString::fromStdString(doc->FieldA(PR_DF_SURNAME)).split(" ");
                                global_PATERNAL_SURNAME1 = surnames.at(0);
                                global_MATERNAL_SURNAME1 = surnames.at(1);
                            }

                            global_CODE_NATIONALITY1 = QString::fromStdString(doc->FieldA(PR_DF_NATIONALITY));
                            global_BIRTH_DATE1 = QString::fromStdString(doc->FieldA(PR_DF_BIRTH_DATE));
                            if(global_BIRTH_DATE1.mid(0,2).toInt() >= 0 && global_BIRTH_DATE1.mid(0,2).toInt() <= 40)
                                global_BIRTH_DATE1 = "20"+global_BIRTH_DATE1.mid(0,2)+"-"+global_BIRTH_DATE1.mid(2,2)+"-"+global_BIRTH_DATE1.mid(4,2);
                            else
                                global_BIRTH_DATE1 = "19"+global_BIRTH_DATE1.mid(0,2)+"-"+global_BIRTH_DATE1.mid(2,2)+"-"+global_BIRTH_DATE1.mid(4,2);

                            enrollPeople("CS");
                        }
                    }
                }
                catch (gxException e)
                {
                    lib1.DisplExcp(e);
                }
                if (doc)
                    delete doc;
                lib1.ProcessEnd();
            }
        }
    }
    catch (gxException e) {
        lib1.DisplExcp(e);
        //  statusBar()->showMessage("ComboScan no conectado...",5);
        //  QPixmap badPix(":/images/bad.png");
        //  ui->label_status_cs->setPixmap(badPix);
    }
}



void formcs::on_pushButton_2_clicked()
{
    readFromFirstDevice();
    if(ui->lineEdit_rut->text()!=""){
        ui->lineEdit_Enterprise->setEnabled(true);
        ui->lineEdit_position->setEnabled(true);
        ui->comboBox_profile->setEnabled(true);
        ui->button_manualRegistration->setEnabled(false);
    }
}

void formcs::enrollPeople(QString device){
    //    Devices:
    //    CS = ComboScan
    //    RT = RTScan
    QString comment;
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if (!qry->exec("select p.rut,p.names,p.paternal_surname,p.birthdate,co.name,p.state,na.code,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone,p.email,po.name,pro.name,p.picture,p.maternal_surname,fr.name from people as p left join company as co on p.rut_company=co.rut left join nationality as na on p.code_nationality=na.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as fr on p.id_frequency=fr.id where p.rut='"+global_PERSONAL_DATA1+"'"))
    {
        QMessageBox::critical(this,tr("ERROR"),error1);
        Logger::insert2Logger(rutSignin," ERROR ", qry->lastError().text()+" "+qry->executedQuery());
    }
    if (!qry->first()) //Person not found in db
    {
        ui->lineEdit_rut->setText(global_PERSONAL_DATA1);

        if(device=="CS")
        {
            ui->lineEdit_name->setText(global_GIVENNAME1);
            ui->lineEdit_appMat->setText(global_MATERNAL_SURNAME1);
            ui->lineEdit_appPat->setText(global_PATERNAL_SURNAME1);
            if(conn.getFirstFromDb(rutSignin, "select take_picture from configuration where key=(select key from user where rut = '"+rutSignin+"')") == "true")
            {
                int ret = QMessageBox::warning(this, tr("Advertencia"),
                                               tr("Persona sin foto, si desea obtener gire cedula al anverso y presione ok."),
                                               QMessageBox::Ok | QMessageBox::Cancel);
                if(ret==QMessageBox::Ok)
                {
                    if(readAnverso(global_PERSONAL_DATA1))
                    {
                        imgPath = QDir::currentPath()+"/people/"+global_PERSONAL_DATA1+".jpg";
                        Logger::insert2Logger(rutSignin," DEBUG ","foto guardada en "+imgPath);
                        QPixmap user(imgPath);
                        user.load(imgPath);
                        ui->formcs_labelImage->setPixmap(user);
                        //no quiero insertar, solo test//conn.insert2Db(rutSignin,"insert into people (rut,names,paternal_surname,maternal_surname,birthdate,state,code_nationality,picture) values ('"+global_PERSONAL_DATA1+"','"+global_GIVENNAME+"','"+global_PATERNAL_SURNAME+"','"+global_MATERNAL_SURNAME+"','"+global_BIRTH_DATE+"','I','"+global_CODE_NATIONALITY+"','"+imgPath+"')");
                    }
                }
                else if(device=="RT")
                {
                    QMessageBox::critical(this,tr("PRECAUCION"),tr("DISPOSITIVO EQUIVOCADO, Persona no se encuentra en la base de datos.Ingreselo con Dipositivo Enrolador(COMBOSCAN)"));
                    //           conn.insert2Db(rutSignin,"insert into people (rut,names,paternal_surname,maternal_surname,birthdate,state,code_nationality,picture) values ('"+global_PERSONAL_DATA+"','"+global_GIVENNAME+"','"+global_PATERNAL_SURNAME+"','"+global_MATERNAL_SURNAME+"','"+global_BIRTH_DATE+"','I','"+global_CODE_NATIONALITY+"','"+imgPath+"')");
                    //conn.insert2Db(rutSignin,"insert into record (datetime_input,rut_people,rut_user,type,state,comment) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+global_PERSONAL_DATA+"','"+rutSignin+"','A','RDB','"+comment+"')");
                }
            }

        }

    }
    else{
        //person is found in the database
        pr1.CloseDevice();
        QMessageBox::information(this,tr("PRECAUCION"),tr("Persona ya se encuentra en la Base de Datos, porfavor escanear con dispositivo lector(RTScann)"));
        formcs::close();
    }

}
bool formcs::readAnverso(QString rut)
{
    string text;
    string ec[]={"Ok","Warning","Error"};

    try
    {
        /* Connecting to the first device */
        lib1.FunctionStart("Connecting to the first device");
        pr1.UseDevice(0,PR_UMODE_FULL_CONTROL);
        lib1.FunctionEnd();

        if (!pr1.IsValid())
        {
            lib1.Error("Failed to initialize!");
        }
        else
        {

            /* Using the device */
            if (!lib1.KbHit()) {
                lib1.ProcessStart("Processing document");
                prDoc * doc = NULL;

                lib1.FunctionStart("Capturing images");
                pr1.Capture();
                lib1.FunctionEnd();

                lib1.FunctionStart("Recognizing.");
                doc = pr1.Recognize(0);
                lib1.FunctionEnd();

                if (!doc->IsValid())
                {
                    lib1.WriteLine("No data found.");
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
                        if (text != "") lib1.WriteLine("[" + lib1.itos(field_code) + "] \"" + text + "\" [" + ec[doc->FieldStatus(field_code)/100] + "]");
                        if(field_code >= PR_DF_FORMATTED) continue;
                        try
                        {
                            gxImage* img = doc->FieldImage(field_code);
                            if(img->IsValid()){
                                if(field_code==2400){
                                    //QString imgPath = QDir::currentPath()+"/release/people/" + rut + ".jpg";
                                    imgPath = QDir::currentPath()+"/people/" + rut + ".jpg";
                                    img->Save(imgPath.toStdString(), GX_JPEG);
                                    return true;
                                }
                            }else{
                                QMessageBox::critical(this,tr("ERROR"),tr("No se pudo obtener la foto, verifique la posicion correcta del carnet y vuelva a intentar"));
                                return false;
                            }
                            if(img) delete img;
                        } catch (gxException e) {
                            lib1.DisplExcp(e);
                            return false;
                        }
                    }
                    delete pdoc;
                }

                if (doc) delete doc;
                lib1.ProcessEnd();
                lib1.WaitForSec(2);
            }

            /* Closing the device */
            lib1.FunctionStart("Closing the device");
            pr1.CloseDevice();
            lib1.FunctionEnd();
        }
    }
    catch (gxException e)
    {
        lib1.DisplExcp(e);
        return false;
    }
}

void formcs::on_pushButton_renewImage_clicked()
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
            ui->formcs_labelImage->setPixmap(user);
        }
    }else if(ui->lineEdit_rut->text().isEmpty())
        QMessageBox::critical(this,tr("PRECAUCION"),tr("Porfavor, presione el boton obtener informacion primero antes de actualizar la imagen"));
}

void formcs::on_lineEdit_Enterprise_textChanged(const QString &arg1)
{
    QStringList companyNames;
    QSqlQuery* query=new QSqlQuery(conn1.mydb);

    //fill the list with company names
    if(query->exec("select name from company")){
        int i=0;
        while(query->next()){
            companyNames.insert(i,query->value(0).toString());
            ++i;
        }
    }
    //qDebug() << "Names Company Found: ";
    //foreach( QString str, companyNames )
    //    qDebug() << str;;
    QCompleter *completer = new QCompleter(companyNames, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_Enterprise->setCompleter(completer);
    /*  if(query->exec("select name from company where name='"+arg1+"'")){
        if(query->next()){
            ui->Button_addEnterprise->setEnabled(false);
            ui->Button_addPosition->setEnabled(false);
        }else if(!ui->Button_addEnterprise->text().isEmpty()){
            ui->Button_addEnterprise->setEnabled(true);
            ui->Button_addPosition->setEnabled(true);
        }
    }*/
}
void formcs::on_lineEdit_position_textChanged(const QString &arg1)
{
    QStringList positionNames;
    QSqlQuery* query=new QSqlQuery(conn1.mydb);
    //fill the list with company names
    if(query->exec("select name from position")){
        int i=0;
        while(query->next()){
            positionNames.insert(i,query->value(0).toString());
            ++i;
        }
    }
    QCompleter *completer = new QCompleter(positionNames, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_position->setCompleter(completer);
}


void formcs::on_button_manualRegistration_clicked()
{
    ui->lineEdit_rut->setEnabled(true);
    ui->lineEdit_name->setEnabled(true);
    ui->lineEdit_Enterprise->setEnabled(true);
    ui->lineEdit_appMat->setEnabled(true);
    ui->lineEdit_appPat->setEnabled(true);
    ui->lineEdit_position->setEnabled(true);
    ui->comboBox_profile->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_renewImage->setEnabled(false);
}

void formcs::on_acceptButton_formcs_clicked()
{
    QString company;
    QString profile;
    QString position;
    bool rut;
    QSqlQuery* query=new QSqlQuery(conn1.mydb);
    //validate rut
    if(query->exec("select * from people where rut='"+ui->lineEdit_rut->text()+"'")){
        if(query->next()&&!ui->lineEdit_rut->text().isEmpty()){
            //found in db
            QMessageBox::warning(this,tr("PRECAUCION"),"El rut :<<"+ui->lineEdit_rut->text()+">> ya se encuentra en la base de datos, Porfavor escanee con dispositivo lector (RTScan)");
            formcs::close();
            rut=true;
        }else
            rut=false;
        //not found
    }


    if(query->exec("select * from company where name='"+ui->lineEdit_Enterprise->text()+"'")){
        if(!query->next()){
            QMessageBox::warning(this,tr("PRECAUCION"),"La empresa <<"+ui->lineEdit_Enterprise->text()+">> no se encuentra en la Base de Datos,porfavor Verifique");
            company="";
        }
        else
            company=query->value(0).toString();
        qDebug()<<company;
    }
    if(query->exec("select * from position where name='"+ui->lineEdit_position->text()+"'")){
        if(!query->next()){
            QMessageBox::warning(this,tr("PRECAUCION"),"El cargo <<"+ui->lineEdit_position->text()+">> no se encuentra en la Base de Datos,porfavor Verifique");
            position="";
        }
        else
            position=query->value(0).toString();
        qDebug()<<position;
    }
    if(query->exec("select * from profile where name='"+ui->comboBox_profile->currentText()+"'")){
        if(query->next()){
            profile=query->value(0).toString();
            qDebug()<<profile;
        }
        else
            profile="";
    }
    //validate enterprise, company and position
    qDebug()<<"current text "+ui->comboBox_profile->currentText();
    if(!company.isEmpty()&&!position.isEmpty()&&!profile.isEmpty()&&rut==false&&!ui->lineEdit_appMat->text().isEmpty()
            &&!ui->lineEdit_appPat->text().isEmpty()&&!ui->lineEdit_appMat->text().isEmpty()){
        QString frequency="2";
        conn1.insert2Db(rutSignin,"insert into people (rut,names,paternal_surname,maternal_surname,birthdate,state,code_nationality,picture,id_position,id_profile,rut_company,id_frequency) values ('"+ui->lineEdit_rut->text().toUpper()+"','"+ui->lineEdit_name->text().toUpper()+"','"+ui->lineEdit_appPat->text().toUpper()+"','"+ui->lineEdit_appMat->text().toUpper()+"','"+global_BIRTH_DATE1+"','I','"+global_CODE_NATIONALITY1+"','"+imgPath+"','"+position+"','"+profile+"','"+company+"','"+frequency+"')");
        if(ui->button_manualRegistration->isEnabled())
            query->exec("insert into record (datetime_input,rut_people,rut_user,type,state) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','M','"+'E'+"')");
        else
            query->exec("insert into record (datetime_input,rut_people,rut_user,type,state) values ('"+currentDate.toString("yyyy-MM-dd")+" "+currentTime.toString("HH:mm")+"', '"+ui->lineEdit_rut->text()+"','"+rutSignin+"','A','"+'E'+"')");
        QMessageBox::information(this,tr("Enhorabuena"),"El  usuario: "+ui->lineEdit_rut->text()+" ha sido ingresado satisfactoriamente");
        pr1.CloseDevice();
        imgPath="";
        clean();
        company="";
        profile="";
        position="";
        rut=false;
        ui->button_manualRegistration->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
    else
        if(ui->lineEdit_Enterprise->text().isEmpty()||ui->lineEdit_position->text().isEmpty()||ui->comboBox_profile->currentText().isEmpty()||ui->lineEdit_rut->text().isEmpty()||ui->lineEdit_appMat->text().isEmpty()||
			 	 ui->lineEdit_appPat->text().isEmpty()||ui->lineEdit_name->text().isEmpty())
            QMessageBox::critical(this,tr("PRECAUCION"),tr("Verifique que todo los campos esten completos y luego presione aceptar nuevamente"));
}





void formcs::on_lineEdit_rut_textChanged(const QString &arg1)
{
    arg1.toUpper();
    ui->lineEdit_rut->setText(ui->lineEdit_rut->text().toUpper());
}

void formcs::on_lineEdit_name_textChanged(const QString &arg1)
{
    ui->lineEdit_name->setText(ui->lineEdit_name->text().toUpper());
}

void formcs::on_lineEdit_appPat_textChanged(const QString &arg1)
{
    ui->lineEdit_appPat->setText(ui->lineEdit_appPat->text().toUpper());
}

void formcs::on_lineEdit_appMat_textChanged(const QString &arg1)
{
    ui->lineEdit_appMat->setText(ui->lineEdit_appMat->text().toUpper());
}
void formcs::clean(){
    //clear all
    QPixmap blueIconUser(":images/User-blue-icon.png");
    ui->formcs_labelImage->setPixmap(blueIconUser);
    ui->lineEdit_rut->setText("");
    ui->lineEdit_name->setText("");
    ui->lineEdit_Enterprise->setText("");
    ui->lineEdit_appMat->setText("");
    ui->lineEdit_appPat->setText("");
    ui->lineEdit_position->setText("");
    ui->comboBox_profile->setCurrentIndex(-1);
    PERSONAL_DATA="";
    GIVENNAME="";
    MATERNAL_SUR="";
    PATERNAL_SUR="";
}