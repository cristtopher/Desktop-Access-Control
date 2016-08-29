#ifndef READWITHOUTCI_H
#define READWITHOUTCI_H

#include <QDialog>

namespace Ui {
class ReadWithoutCI;
}

class ReadWithoutCI : public QDialog
{
    Q_OBJECT

public:
    explicit ReadWithoutCI(QWidget *parent = 0);
    ~ReadWithoutCI();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_register_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_rut_editingFinished();

    void clean();

    void on_listView_imput_clicked();

    void on_lineEdit_patent_output_editingFinished();

    void on_lineEdit_patent_input_editingFinished();

    void on_lineEdit_comment_editingFinished();

    QString verifyPeople();

    void on_lineEdit_patent_input_textChanged(const QString &arg1);

private:
    Ui::ReadWithoutCI *ui;
};

#endif // READWITHOUTCI_H
