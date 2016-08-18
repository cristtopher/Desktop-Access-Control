#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>  // necesario para debugueo de nombre de puertos :P
#include <QObject>
#include <QSignalMapper>
#include <QAxObject>
#include <iostream>


extern QString PERSONAL_DATA; //rut.
extern QString GIVENNAME;
extern QString MATERNAL_SUR;
extern QString PATERNAL_SUR;



namespace Ui {
class Dashboard;
}


class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = 0);
    ~Dashboard();

public slots:

    void handlePeople(QString device);

    void loadLCD();

    void loadTables(QString type);

private slots:

    void on_actionExportar_triggered();

    void on_actionRegistro_Manual_triggered();

    void exit();

    void on_actionSalir_triggered();

    void BuildTables();

    void clean(QString type, bool personalPanel);

    void on_actionHistorial_triggered();

    void on_lineEdit_filtered_textChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void readFromPR();

    bool connectComboScan();

    void on_pushButton_clicked();

    void on_pushButton_rejected_clicked();

    void on_tableWidget_input_cellClicked(int row, int column);

    bool comboScanIsOpen();

    void on_tableWidget_input_cellChanged(int row, int column);

    void on_actionDetectar_ComboScan_triggered();

    bool readAnverso(QString rut);

    void loopComboScan();

    void on_tableWidget_output_cellChanged(int row, int column);

    void on_actionCerrar_Sesi_n_triggered();

    void showTime();

    void on_actionImportarPersonas_triggered();

    void on_actionAdministrarPersonas_triggered();

    void on_actionAdministrarUsuarios_triggered();

    void on_actionImportarEmpresas_triggered();

    void on_actionImportarCargos_triggered();

    void on_actionImportarPerfiles_triggered();

    void bloodPanel(int segs);

    void on_actionAdministrarEmpresas_triggered();

    void on_actionActualizar_triggered();

    void on_lineEdit_pdf417_editingFinished();

    void on_lineEdit_pdf417_selectionChanged();

    void on_pushButton_userProfile_clicked();

    void on_actionIndividual_triggered();

    void on_actionRechazados_triggered();

    void on_actionConfiguraci_n_triggered();

    bool RtIsConnected();

    void on_actionDiario_triggered();

    void serialReceived();

    void on_lineEdit_pdf417_textChanged(const QString &arg1);

    void on_actionDetectar_RTScan_triggered();

    void on_actionGeneral_triggered();

    void on_pushButton_updatePic_clicked();

    void on_actionEnrolar_triggered();


private:
    Ui::Dashboard *ui;
    enum people
    {
        RUT,NAMES,PATERNAL_SURNAME,BIRTHDATE,COMPANY,STATE,COD_NATIONALITY,START_AUTHORIZED_HOUR,
        END_AUTHORIZED_HOUR,START_AUTHORIZED_DATE,END_AUTHORIZED_DATE,CELLPHONE,EMAIL,POSITION,
        PROFILE,PICTURE,MATERNAL_SURNAME,FREQUENCY
    };

    QByteArray serialData;
    QString serialBuffer;
    QString rutValidate(QString rut_sin_dv);
};

#endif // DASHBOARD_H
