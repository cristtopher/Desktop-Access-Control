#include "logger.h"
#include "ui_logger.h"

#include "connection.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>

Logger::Logger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logger)
{
    ui->setupUi(this);

    QFile file("./AccessControl.log");
    if(file.open(QFile::ReadOnly|QFile::Truncate)){
        QTextStream in(&file);
        QString text = in.readAll();
        file.close();
        ui->plainTextEdit->setPlainText(text);
    }
    else
    {
        QMessageBox::critical(this, tr("ERROR"), tr("Error al leer log, este no existe"));
    }
}

void Logger::insert2Logger(const QString rut_user, const QString level, const QString event)
{
    QFile fileName("AccessControl.log");
    if(fileName.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream textStream(&fileName);
        QDateTime currentDateTime = QDateTime::currentDateTime();
        textStream << currentDateTime.toString("yyyy-MM-dd h:m:s") << level << rut_user+": " << event << "\n";
        fileName.close();
    }
    else
        qDebug()<<"log file not found";
}

Logger::~Logger()
{
    delete ui;
}
