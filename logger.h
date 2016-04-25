#ifndef LOGGER_H
#define LOGGER_H

#include <QDialog>

namespace Ui {
class Logger;
}

class Logger : public QDialog
{
    Q_OBJECT

public:
    explicit Logger(QWidget *parent = 0);
    ~Logger();

public:
    static void insert2Logger(const QString rut_user, const QString level, const QString event);

private:
    Ui::Logger *ui;
};

#endif // LOGGER_H
