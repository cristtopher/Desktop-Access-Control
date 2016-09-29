#ifndef COMPANIES_H
#define COMPANIES_H

#include <QDialog>
extern QString selectedCompany;

namespace Ui {
class Companies;
}

class Companies : public QDialog
{
    Q_OBJECT

public:
    explicit Companies(QWidget *parent = 0);
    ~Companies();

public:
    void loadTable(QString query);

private slots:
    void on_lineEdit_search_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_update_clicked();

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_pushButton_new_clicked();

    void on_pushButton_newCompany_clicked();
	void clean(QString type, bool personalPanel);
private:
    Ui::Companies *ui;
};

#endif // COMPANIES_H
