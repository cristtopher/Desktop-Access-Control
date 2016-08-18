#include "dashboard.h"
#include <QApplication>
#include <login.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	 Login log;
    Dashboard dash;
    log.show();

    return a.exec();
}
