#include "people.h"
#include "ui_people.h"

#include "connection.h"
#include "logger.h"
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QCompleter>




People::People(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::People)
{
    ui->setupUi(this);
    this->setWindowTitle("Control de accesos - Administrador de personas");
    ui->pushButton_new->setEnabled(false);

    connection conn;
        /*
    if(!conn.isOpen()){
        QMessageBox::critical(this,tr("ERROR"),tr("Error al establecer conexion con base de datos"));
        QPixmap db_bad(":images/Database-Delete-icon.png");
        ui->label_status->setPixmap(db_bad);
    }
    else
    {*/
        QPixmap db_ok(":images/Database-Accept-icon.png");
        ui->label_status->setPixmap(db_ok);
        ui->lineEdit_rut->setFocus();

        QSqlQueryModel * nacionalityModal=new QSqlQueryModel();
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        qry->exec("select name from nationality order by name asc");
        nacionalityModal->setQuery(*qry);
        ui->comboBox_nationality->setModel(nacionalityModal);
        ui->comboBox_nationality->setCurrentIndex(ui->comboBox_nationality->findText("Chile"));

        QSqlQueryModel * profileModal=new QSqlQueryModel();
        qry->exec("select name from profile order by name asc");
        profileModal->setQuery(*qry);
        ui->comboBox_profile->setModel(profileModal);
        ui->comboBox_profile->setCurrentIndex(-1);

        QSqlQueryModel * positionModal=new QSqlQueryModel();
        qry->exec("select name from position order by name asc");
        positionModal->setQuery(*qry);
        ui->comboBox_position->setModel(positionModal);
        ui->comboBox_position->setCurrentIndex(-1);

        QSqlQueryModel * companyModal=new QSqlQueryModel();
//        qry->prepare("select name || ' (' || rut || ')' from company order by name asc");
        qry->exec("select name from company order by name asc");
        companyModal->setQuery(*qry);
        ui->comboBox_company->setModel(companyModal);
        ui->comboBox_company->setCurrentIndex(-1);

        QCompleter *completer = new QCompleter(this);
        completer->setModel(companyModal);
        ui->comboBox_company->setCompleter(completer);

        QSqlQueryModel * frequencyModal=new QSqlQueryModel();
        qry->exec("select name from frequency order by name asc");
        frequencyModal->setQuery(*qry);
        ui->comboBox_frequency->setModel(frequencyModal);
        ui->comboBox_frequency->setCurrentIndex(ui->comboBox_frequency->findText("TEMPORAL"));

        ui->comboBox_state->addItem("ACTIVO", "A");
        ui->comboBox_state->addItem("INACTIVO","I");

        ui->dateEdit_start->setDate(QDate::currentDate());
        ui->dateEdit_end->setDate(QDate::currentDate().addDays(1));

        ui->timeEdit_start->setTime(QTime::fromString("08:00"));
        ui->timeEdit_end->setTime(QTime::fromString("18:00"));

        ui->pushButton_update->setEnabled(false);

        //loading record head for filtered by combobox
        ui->comboBox_filtered->addItem("Rut","rut");
        ui->comboBox_filtered->addItem("Nombres","names");
        ui->comboBox_filtered->addItem("Apellido Paterno","paternal_surname");
        ui->comboBox_filtered->addItem("Apellido Materno","maternal_surname");
        ui->comboBox_filtered->addItem("Estado","state");
        ui->comboBox_filtered->addItem("Empresa","empresa");

        //para obtener index seleccionado
        //QString state =  ui->comboBox_state->itemText(ui->comboBox_state->currentIndex());

        loadTable("default");
    }
//}

People::~People()
{
    delete ui;
}

void People::loadTable(QString query){
   connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);
    if(query=="default")
       // qry->prepare("select p.rut as Rut,p.names as Nombres,p.paternal_surname as 'Apellido Paterno',p.maternal_surname as 'Apellido Materno',c.name as Empresa,(CASE WHEN p.state == 'A' THEN 'ACTIVO' ELSE 'INACTIVO' END) as Estado,n.name as Nacionalidad,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone as Telefono,p.email as Correo,po.name as Cargo,pro.name as Perfil,p.picture as Imagen,f.name as Frecuencia from people as p left join company as c on p.rut_company=c.rut left join nationality as n on p.code_nationality=n.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as f on p.id_frequency=f.id");
		qry->prepare("select p.rut as Rut,p.names as Nombres,p.paternal_surname as Apellido_Paterno,p.maternal_surname as Apellido_Materno,c.name as Empresa,(CASE WHEN p.state = 'A' THEN 'ACTIVO' ELSE 'INACTIVO' END) as Estado,n.name as Nacionalidad,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone as Telefono,p.email as Correo,po.name as Cargo,pro.name as Perfil,p.picture as Imagen,f.name as Frecuencia from people as p left join company as c on p.rut_company=c.rut left join nationality as n on p.code_nationality=n.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as f on p.id_frequency=f.id");
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
    }
    delete qry;
}

void People::on_lineEdit_rut_editingFinished()
{
    if(validateChnId(ui->lineEdit_rut->text())==false){
        QMessageBox::critical(this,tr("Error"),tr("Rut invalido"));
        ui->lineEdit_rut->setFocus();
    }
}

void People::on_lineEdit_names_editingFinished()
{
    ui->lineEdit_names->setText(ui->lineEdit_names->text().toUpper());
}

void People::on_lineEdit_paternal_surname_editingFinished()
{
    ui->lineEdit_paternal_surname->setText(ui->lineEdit_paternal_surname->text().toUpper());
}

void People::on_lineEdit_maternal_surname_editingFinished()
{
    ui->lineEdit_maternal_surname->setText(ui->lineEdit_maternal_surname->text().toUpper());
}

void People::on_lineEdit_email_editingFinished()
{
//    if(ui->lineEdit_email->text().isEmpty())
//    {
//        ui->lineEdit_email->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
//        ui->lineEdit_email->setFocus();
//    }
//    else if(!ui->lineEdit_email->text().contains("@") || !ui->lineEdit_email->text().contains("."))
//    {
//        ui->lineEdit_email->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//        ui->lineEdit_email->setFocus();
//    }
//    else
//        ui->lineEdit_email->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
    ui->lineEdit_email->setText(ui->lineEdit_email->text().toUpper());
}

void People::on_dateEdit_end_editingFinished()
{
    //validar que este sea mayor al dateEdit_start
}

bool People::validateChnId(QString rut)
{
    //vectorizar rut
//    QVector<QString> vrut(rut.length());
//    int i;
//    //invertimos
//    for(i = rut.length(); i >= 0 ; i--) {
//        vrut.append(rut.at(i));
//        qDebug()<<rut.at(i);
//    }
//    for(i = 0; i <= vrut.size(); i++) {
//        qDebug()<<vrut.at(i);
//    }
//    int s;
//    int c=2;
//    for(i=0; i <= vrut.size(); i++){
//        s=s+(vrut.at(i).toInt() * c);
//        c++;
//    }
//    qDebug()<<c;
//    int Ri = c%11;
//    int Rf = 11-Ri;
//    QString dv;
//    if(Rf==11){
//        dv="0";
//    }else if(Rf==10){
//        dv="K";
//    }else if(Rf<10){
//        dv=Rf;
//    }

//    qDebug()<<dv;
//    if(vrut.at(rut.length())==dv){
//        return true;
//    }else{
//        return false;
//    }
    return true;
}
void People::on_lineEdit_names_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->styleSheet().contains("QLineEdit { background: rgb(255, 121, 121);}"))
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
    ui->lineEdit_names->setText(ui->lineEdit_names->text().toUpper());
}

void People::on_lineEdit_rut_textChanged()
{
    QString rut = ui->lineEdit_rut->text();
    rut.replace("-", "");
    rut.replace(".","");
    rut.toUpper();
    rut.remove(QRegularExpression("[A-J]"));
    rut.remove(QRegularExpression("[L-Z]"));
    ui->lineEdit_rut->setText(rut);
//    if(ui->lineEdit_rut->styleSheet().contains("QLineEdit { background: rgb(255, 121, 121);}"))
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);}");
}

void People::on_lineEdit_paternal_surname_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->text().isEmpty())
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
    ui->lineEdit_paternal_surname->setText(ui->lineEdit_paternal_surname->text().toUpper());
}

void People::on_lineEdit_maternal_surname_textChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->text().isEmpty())
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_paternal_surname->text().isEmpty())
//        ui->lineEdit_paternal_surname->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
    ui->lineEdit_maternal_surname->setText(ui->lineEdit_maternal_surname->text().toUpper());
}

void People::on_dateEdit_birthdate_userDateChanged()
{
//    if(ui->lineEdit_rut->text().isEmpty())
//        ui->lineEdit_rut->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_names->text().isEmpty())
//        ui->lineEdit_names->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_paternal_surname->text().isEmpty())
//        ui->lineEdit_paternal_surname->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
//    if(ui->lineEdit_maternal_surname->text().isEmpty())
//        ui->lineEdit_maternal_surname->setStyleSheet("QLineEdit { background: rgb(255, 121, 121);}");
}

void People::on_comboBox_frequency_currentIndexChanged(int index)
{
    QString frequency =  ui->comboBox_frequency->itemText(index);
    if(frequency == "PERMANENTE")
    {
        ui->dateEdit_end->setDate(QDate::fromString("31/12/9999"));
        ui->dateEdit_end->setEnabled(false);

    }
    else
        ui->dateEdit_end->setEnabled(true);
}

void People::on_lineEdit_cellphone_textChanged()
{
    QString cellphone = ui->lineEdit_cellphone->text();
    cellphone.remove(QRegularExpression("[A-Z]"));
    cellphone.remove(QRegularExpression("[a-z]"));
    cellphone.replace("+","");
    cellphone.replace("-","");
    cellphone.replace("(","");
    cellphone.replace(")","");
    ui->lineEdit_cellphone->setText(cellphone);
}

void People::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column()==0){
        ui->pushButton_update->setEnabled(true);
        QString rut = ui->tableView->model()->data(index).toString();
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        if(qry->exec("select names,paternal_surname,maternal_surname,birthdate,email,cellphone,na.name,co.name,fr.name,pos.name,pro.name,p.state,p.start_authorized_date,p.end_authorized_date,p.start_authorized_hour,p.end_authorized_hour from people as p left join nationality as na on p.code_nationality=na.code left join company as co on p.rut_company=co.rut left join frequency as fr on p.id_frequency=fr.id left join position as pos on p.id_position=pos.id left join profile as pro on p.id_profile=pro.id where p.rut = '"+rut+"'")){
            qDebug()<<qry->lastQuery();
            while (qry->next()) {
                ui->lineEdit_rut->setText(rut);
                ui->lineEdit_names->setText(qry->value(0).toString());
                ui->lineEdit_paternal_surname->setText(qry->value(1).toString());
                ui->lineEdit_maternal_surname->setText(qry->value(2).toString());
                ui->dateEdit_birthdate->setDate(QDate::fromString(qry->value(3).toString(),"yyyy-MM-dd"));
                ui->lineEdit_email->setText(qry->value(4).toString());
                ui->lineEdit_cellphone->setText(qry->value(5).toString());

                ui->dateEdit_start->setDate(QDate::fromString(qry->value(12).toString(), "yyyy-MM-dd"));
                ui->dateEdit_end->setDate(QDate::fromString(qry->value(13).toString(), "yyyy-MM-dd"));

                ui->timeEdit_start->setTime(QTime::fromString(qry->value(14).toString()));
                ui->timeEdit_end->setTime(QTime::fromString(qry->value(15).toString()));

                int index_nationality = ui->comboBox_nationality->findText(qry->value(6).toString());
                if (index_nationality != -1) // -1 for not found
                    ui->comboBox_nationality->setCurrentIndex(index_nationality);

                int index_company = ui->comboBox_company->findText(qry->value(7).toString());
                if (index_company != -1)// -1 for not found
                    ui->comboBox_company->setCurrentIndex(index_company);
                
                else
                    ui->comboBox_company->setCurrentIndex(-1);

                int index_frequency = ui->comboBox_frequency->findText(qry->value(8).toString());
                if (index_frequency != -1) // -1 for not found
                    ui->comboBox_frequency->setCurrentIndex(index_frequency);
                else
                    ui->comboBox_company->setCurrentIndex(-1);

                int index_position = ui->comboBox_position->findText(qry->value(9).toString());
                if (index_position != -1) // -1 for not found
                    ui->comboBox_position->setCurrentIndex(index_position);
                else
                    ui->comboBox_position->setCurrentIndex(-1);

                int index_profile = ui->comboBox_profile->findText(qry->value(10).toString());
                if (index_profile != -1) // -1 for not found
                    ui->comboBox_profile->setCurrentIndex(index_profile);
                else
                    ui->comboBox_profile->setCurrentIndex(-1);

                if(qry->value(11).toString()=="A")
                    ui->comboBox_state->setCurrentIndex(0);
                else
                    ui->comboBox_state->setCurrentIndex(1);
            }
        }
        delete qry;
    }
}

void People::on_pushButton_new_clicked()
{
    ui->lineEdit_rut->clear();
    ui->lineEdit_names->clear();
    ui->lineEdit_paternal_surname->clear();
    ui->lineEdit_maternal_surname->clear();
    ui->dateEdit_birthdate->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_cellphone->clear();

    ui->comboBox_nationality->setCurrentIndex(-1);
    ui->comboBox_company->setCurrentIndex(-1);
    ui->comboBox_frequency->setCurrentIndex(-1);
    ui->comboBox_position->setCurrentIndex(-1);
    ui->comboBox_profile->setCurrentIndex(-1);
    ui->comboBox_state->setCurrentIndex(-1);
}

void People::on_lineEdit_filtered_textChanged(const QString &arg1)
{
    QString query;
    //for after deleting all.
    if(arg1.isEmpty())
        query = "default";
    else
    {
        int indexSelected = ui->comboBox_filtered->currentIndex();
        switch(indexSelected)
        {
        case 0: //rut
        case 1: //names
        case 2: //paternal_surname
        case 3: //maternal_surname
        case 4: //state
            query = "select p.rut as Rut,p.names as Nombres,p.paternal_surname as 'Apellido Paterno',p.maternal_surname as 'Apellido Materno',c.name as Empresa,(CASE WHEN p.state == 'A' THEN 'ACTIVO' ELSE 'INACTIVO' END) as Estado,n.name as Nacionalidad,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone as Telefono,p.email as Correo,po.name as Cargo,pro.name as Perfil,p.picture as Imagen,f.name as Frecuencia from people as p left join company as c on p.rut_company=c.rut left join nationality as n on p.code_nationality=n.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as f on p.id_frequency=f.id where p."+ui->comboBox_filtered->itemData(indexSelected).toString()+" like '"+arg1+"%'";
            break;
        case 5: //company
            query = "select p.rut as Rut,p.names as Nombres,p.paternal_surname as 'Apellido Paterno',p.maternal_surname as 'Apellido Materno',c.name as Empresa,(CASE WHEN p.state == 'A' THEN 'ACTIVO' ELSE 'INACTIVO' END) as Estado,n.name as Nacionalidad,p.start_authorized_hour,p.end_authorized_hour,p.start_authorized_date,p.end_authorized_date,p.cellphone as Telefono,p.email as Correo,po.name as Cargo,pro.name as Perfil,p.picture as Imagen,f.name as Frecuencia from people as p left join company as c on p.rut_company=c.rut left join nationality as n on p.code_nationality=n.code left join position as po on p.id_position=po.id left join profile as pro on p.id_profile=pro.id left join frequency as f on p.id_frequency=f.id where c.name like '"+arg1+"%'";
            break;
        }
    }
    loadTable(query);
}

void People::on_tableView_activated(const QModelIndex &index)
{

}

void People::on_pushButton_update_clicked()
{
    connection conn;
    QSqlQuery* qry=new QSqlQuery(conn.mydb);

    QString company=conn.getFirstFromDb(rutSignin,"select rut from company where name = '"+ui->comboBox_company->currentText()+"'");
    QString state;
    if(ui->comboBox_state->currentText()=="ACTIVO")
        state="A";
    else
        state="I";
    QString nationality=conn.getFirstFromDb(rutSignin,"select code from nationality where name = '"+ui->comboBox_nationality->currentText()+"'");
    QString position=conn.getFirstFromDb(rutSignin,"select id from position where name = '"+ui->comboBox_position->currentText()+"'");
    QString profile=conn.getFirstFromDb(rutSignin,"select id from profile where name = '"+ui->comboBox_profile->currentText()+"'");
    QString frequency=conn.getFirstFromDb(rutSignin,"select id from frequency where name = '"+ui->comboBox_frequency->currentText()+"'");
    QString cellphone = ui->lineEdit_cellphone->text();
    QString email = ui->lineEdit_email->text();

	if(!ui->lineEdit_rut->text().isEmpty()){
   if(!qry->exec("UPDATE people SET names='"+ui->lineEdit_names->text()+
                 "',paternal_surname='"+ui->lineEdit_paternal_surname->text()+"',maternal_surname='"+ui->lineEdit_maternal_surname->text()+
                 "',birthdate='"+ui->dateEdit_birthdate->text()+"',email='"+email+"',cellphone='"+
                 cellphone+"',start_authorized_hour='"+ui->timeEdit_start->text()+"',end_authorized_hour='"+
                 ui->timeEdit_end->text()+"',state='"+state+"',start_authorized_date='"+ui->dateEdit_start->text()+"',end_authorized_date='"+ui->dateEdit_end->text()+
                 "',code_nationality='"+nationality+"',id_position='"+position+"',id_profile='"+profile+"',id_frequency='"+frequency+"',rut_company='"+company+"'"+
                 " where rut='"+ui->lineEdit_rut->text()+"'"))
    {
        QMessageBox::critical(this,tr("Error al registrar"),error1);
        Logger::insert2Logger(rutSignin, " ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
    }
    else
    {
        QMessageBox::information(this,"ACTUALIZACION", tr("Persona actualizada exitosamente."));
        Logger::insert2Logger(rutSignin, " DEBUG ", qry->lastQuery());
        ui->dateEdit_start->setDate(QDate::fromString(conn.getFirstFromDb(rutSignin,"select start_authorized_date from people where rut = '"+ui->lineEdit_rut->text()+"'")));
        ui->dateEdit_end->setDate(QDate::fromString(conn.getFirstFromDb(rutSignin,"select end_authorized_date from people where rut = '"+ui->lineEdit_rut->text()+"'")));
    }
   }else
        QMessageBox::information(this,"PRECAUCION", tr("Campo RUT vacio,porfavor Verifique"));
    delete qry;
    loadTable("default");
}

void People::on_pushButton_add_clicked()
{
    connection conn;
    if(People::validateChnId(ui->lineEdit_rut->text()))
    {
        if(!ui->lineEdit_names->text().isEmpty())
        {
            if(conn.getFirstFromDb(rutSignin,"select rut from people where rut='"+ui->lineEdit_rut->text()+"'")!="")
            {
                QMessageBox::warning(this,tr("WARNING"),tr("Persona ya existe."));
            }
            else{
                if(!ui->lineEdit_paternal_surname->text().isEmpty())
                {
                    if(!ui->lineEdit_maternal_surname->text().isEmpty())
                    {
                        if(ui->dateEdit_end->date().daysTo(ui->dateEdit_end->date()) < 0)
                        {
                            QMessageBox::warning(this, tr("Error"),tr("La fecha fin no puede ser menor a la fecha de inicio"));
                            ui->dateEdit_end->setFocus();
                        }
                        else
                        {
                            QString rut_company = conn.getFirstFromDb(rutSignin,"select rut from company where name='"+ui->comboBox_company->itemText(ui->comboBox_company->currentIndex())+"'");
                            QString id_nationality = conn.getFirstFromDb(rutSignin,"select code from nationality where name='"+ui->comboBox_nationality->itemText(ui->comboBox_nationality->currentIndex())+"'");
                            QString id_position = conn.getFirstFromDb(rutSignin,"select id from position where name='"+ ui->comboBox_position->itemText(ui->comboBox_position->currentIndex())+"'");
                            QString id_profile = conn.getFirstFromDb(rutSignin,"select id from profile where name='"+ ui->comboBox_profile->itemText(ui->comboBox_profile->currentIndex())+"'");
                            QString id_frequency = conn.getFirstFromDb(rutSignin,"select id from frequency where name='"+ ui->comboBox_frequency->itemText(ui->comboBox_frequency->currentIndex())+"'");
                            QString state = ui->comboBox_state->itemData(ui->comboBox_state->currentIndex()).toString();

    //                        if(id_position.isEmpty())
    //                            id_position=" ";
    //                        if(id_profile.isEmpty())
    //                            id_profile=" ";

                            if(rut_company.isEmpty())
                                QMessageBox::critical(this,tr("ERROR"),tr("Debe seleccionar empresa primero."));
                            else
                            {
                                QString query;
                                if(ui->comboBox_frequency->itemText(ui->comboBox_frequency->currentIndex())=="PERMANENTE"){
                                    query=tr("insert into people (rut, names, paternal_surname, maternal_surname, birthdate, rut_company, state, code_nationality, ")
                                        + tr("start_authorized_hour, end_authorized_hour,start_authorized_date, end_authorized_date, cellphone, email, id_position, ")
                                        +"id_profile, id_frequency) values ('"+ui->lineEdit_rut->text()+"','"+ui->lineEdit_names->text()+"','"+ui->lineEdit_paternal_surname->text()+"','"
                                        +ui->lineEdit_maternal_surname->text()+"','"+ui->dateEdit_birthdate->text()+"','"
                                        +rut_company+"','"+state+"','"+id_nationality+"','"+ui->timeEdit_start->text()+"','"+ui->timeEdit_end->text()+"','"+ui->dateEdit_start->text()+"','""','"
                                        +ui->lineEdit_cellphone->text()+"','"+ui->lineEdit_email->text()+"','"+id_position+"','"+id_profile+"','"+id_frequency+"')";
                                }else
                                    query=tr("insert into people (rut, names, paternal_surname, maternal_surname, birthdate, rut_company, state, code_nationality, ")
                                        + tr("start_authorized_hour, end_authorized_hour,start_authorized_date, end_authorized_date, cellphone, email, id_position, ")
                                        +"id_profile, id_frequency) values ('"+ui->lineEdit_rut->text()+"','"+ui->lineEdit_names->text()+"','"+ui->lineEdit_paternal_surname->text()+"','"
                                        +ui->lineEdit_maternal_surname->text()+"','"+ui->dateEdit_birthdate->text()+"','"
                                        +rut_company+"','"+state+"','"+id_nationality+"','"+ui->timeEdit_start->text()+"','"+ui->timeEdit_end->text()+"','"+ui->dateEdit_start->text()+"','"
                                        +ui->dateEdit_end->text()+"','"+ui->lineEdit_cellphone->text()+"','"+ui->lineEdit_email->text()+"','"+id_position+"','"+id_profile+"','"+id_frequency+"')";

                                if(connection::insert2Db(rutSignin,query)){
                                    QMessageBox::information(this,tr("INFO"),tr("Persona agregada exitosamente."));

                                    loadTable("default");
                                }
                                else
                                {
                                    QMessageBox::critical(this, tr("ERROR"), tr("Error al agregar usuario."));
                                }
                            }
                        }
                    }
                    else
                    {
                        QMessageBox::critical(this, tr("Error"), tr("Ingrese apellido materno."));
                        ui->lineEdit_maternal_surname->setFocus();
                    }
                }
                else
                {
                    QMessageBox::critical(this, tr("Error"), tr("Ingrese apellido paterno."));
                    ui->lineEdit_paternal_surname->setFocus();
                }
            }
        }
        else
        {
            QMessageBox::critical(this, tr("Error"), tr("Ingrese nombres."));
            ui->lineEdit_names->setFocus();
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("Rut ingresado no es valido."));
        ui->lineEdit_rut->setFocus();
    }
}
