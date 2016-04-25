#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = 0);
    ~Profile();

private:
    Ui::Profile *ui;
};

#endif // PROFILE_H
