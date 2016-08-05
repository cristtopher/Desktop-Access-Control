#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QtDebug>
#include <QString>
#include "logger.h"
#include <QMessageBox>

extern QString rutSignin;
extern QString error0;
extern QString error1;
extern QString rtPort;

class connection
{

public:
    QSqlDatabase mydb;
    bool debug;

    bool isOpenDB(){
        if(mydb.open())
            return debug= true;
        else
            return debug=false;
        qDebug() <<"boolean base de datos "+debug;
    }


    bool isOpen(){
        if(mydb.isOpen())
            return true;
        else
            return false;
    }

    void connClose()
    {
        if(mydb.isOpen())
        {
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);
        }
        else
            Logger::insert2Logger(rutSignin," ERROR ", "Tratando de cerrar DB ya cerrada...");
    }

    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(QDir::currentPath()+"/db/AccessControl.db");
//        mydb.setDatabaseName("C:/Users/jmora/Desktop/db/AccessControl.db");
//        mydb.setDatabaseName("E:/14116/db/AccessControl.db");

        if(!mydb.open())
        {
            Logger::insert2Logger(rutSignin," ERROR ", mydb.lastError().text());
            return false;
        }
        else
            return true;
    }
    static bool insert2Db(const QString rut_user, const QString insert)
    {
        if(!insert.isEmpty()){
            connection conn;
            QSqlQuery* qry=new QSqlQuery(conn.mydb);
            qry->prepare(insert);
            if(qry->exec())
            {
                Logger::insert2Logger(rut_user," DEBUG ", qry->executedQuery());
                return true;
            }
            else
            {
                Logger::insert2Logger(rut_user," ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
                return false;
            }
        }
        else
           return false;
    }

    static QString getFirstFromDb(const QString rut_user, const QString query)
    {
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        qry->prepare(query);
        if(qry->exec())
        {
            qry->first();
            if(!(qry->value(0).toString().isEmpty() or qry->value(0).toString().isNull()))
            {
                Logger::insert2Logger(rut_user," DEBUG ", query);
                return qry->value(0).toString();
            }
            else
            {
//                Logger::insert2Logger(rut_user," EMPTY ", qry->executedQuery());
                return "";
            }
        }
        else
        {
            Logger::insert2Logger(rut_user," ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
            return "";
        }
    }

    static QString getLastFromDb(const QString rut_user, const QString query)
    {
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        qry->prepare(query);
        if(qry->exec())
        {
            qry->last();
            if(qry->value(0).toString().isEmpty() or qry->value(0).toString().isNull())
                return qry->value(0).toString();
            else
                return "";
        }
        else
        {
            Logger::insert2Logger(rut_user," ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
            return "";
        }
    }

    static void updateDb(const QString rut_user, const QString query)
    {
        connection conn;
        QSqlQuery* qry=new QSqlQuery(conn.mydb);
        qry->prepare(query);
        if(!qry->exec())
            Logger::insert2Logger(rut_user," ERROR ", qry->lastError().text()+" -> "+qry->executedQuery());
        else
            Logger::insert2Logger(rut_user," DEBUG ", qry->executedQuery());
    }

public:
    connection();
};

#endif // CONNECTION_H
